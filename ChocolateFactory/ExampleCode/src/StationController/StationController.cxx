/*
 * (c) 2021 Copyright, Real-Time Innovations, Inc. (RTI) All rights reserved.
 *
 * RTI grants Licensee a license to use, modify, compile, and create derivative
 * works of the software solely for use with RTI Connext DDS.  Licensee may
 * redistribute copies of the software provided that all such copies are
 * subject to this license. The software is provided "as is", with no warranty
 * of any type, including any warranty for fitness for any purpose. RTI is
 * under no obligation to maintain or support the software.  RTI shall not be
 * liable for any incidental or consequential damages arising out of the use or
 * inability to use the software.
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "StationController.hpp"
#include "../CommonInfrastructure/EnumPrintHelpers.hpp"

using namespace std;
using namespace com::chocolatefactory::generated;

void PrintHelp();

// ------------------------------------------------------------------------- //
//
// Station Controller Application:
// This application acts as a "station controller" in a chocolate factory. Its
// purpose is to process a chocolate lot according to a recipe for the chocolate
// either dark chocolate, milk chocolate, or white chocolate.
//
// To "process" a lot, this application retrieves the recipe that this lot is
// using, and based on how much time the step should take, it sleeps.
//
// This application receives:
//     1. Recipe data: it receives recipes so it can get information on how to
//        process a particular lot.  (Note that this exmaple replaces real
//        recipe information with how long to sleep)
//     2. Filtered chocolate lot state updates: this application creates a
//        content-filtered topic, so it receives only updates about chocolate
//        lots that:
//          a. Are assigned to it, or
//          b. Are completed (so it can unregister that lot)
//
// This application sends:
//     1. Updates to a chocolate state saying either:
//          a. It is waiting at this station controller
//          b. This station controller is processing it
//          c. It is assigned to the next station controller in the recipe
//          d. It is completed (no more station controllers in the recipe)
//
// ------------------------------------------------------------------------- //

int main(int argc, char* argv[])
{
    int sec = 0;

    int controllerType = 1;
    string setting;
    bool multicastAvailable = true;

    for (int i = 0; i < argc; i++) {
        // There are five types of valid controller described in the IDL type
        // StationControllerKind: Sugar controller, cocoa butter controller
        // cocoa liquor controller, vanilla controller, and milk controller
        if (0 == strcmp(argv[i], "--controller-type")) {
            ++i;
            if (i == argc) {
                cout << "Bad parameter: Did not pass a station controller type"
                     << endl;
                return -1;
            }
            controllerType = atoi(argv[i]);

            // Only curently have 5 types of controller
            if (controllerType < 1 || controllerType > 5) {
                cout << "Bad parameter: controller types are between 1 and 5"
                     << endl;
                return -1;
            }
        } else if (0 == strcmp(argv[i], "--no-multicast")) {
            multicastAvailable = false;
        } else if (0 == strcmp(argv[i], "--help")) {
            PrintHelp();
            return 0;
        } else if (i > 0) {
            // If we have a parameter that is not the first one, and is not
            // recognized, return an error.
            cout << "Bad parameter: " << argv[i] << endl;
            PrintHelp();
            return -1;
        }
    }

    // Set up paths for XML files.  The profiles are for applications that
    // have no multicast available at all, or that have multicast available
    // on the network.
    vector<string> xmlFiles;

    if (multicastAvailable) {
        // Adding the XML files that contain profiles used by this application
        xmlFiles.push_back("file://../src/Config/base_profile_multicast.xml");
        xmlFiles.push_back(
                "file://../src/Config/recipe_profiles_multicast.xml");
    } else {
        // Adding the XML files that contain profiles used by this application
        xmlFiles.push_back(
                "file://../src/Config/base_profile_no_multicast.xml");
        xmlFiles.push_back(
                "file://../src/Config/recipe_profiles_no_multicast.xml");
    }

    try {
        // This sets up the data interface for the station controller - what
        // data it sends and receives over the network, along with the quality
        // of service.  From the standpoint of RTI Connext, this is where
        // the most interesting code is that sets up all of the objects that
        // allow the application to communicate over shared memory or over
        // the network
        StationControllerInterface stationControllerInterface(
                        (StationControllerKind) controllerType,
                        xmlFiles, QOS_PROFILE_STATE_DATA);

        // Create a new Station Controller object.
        StationController controller((StationControllerKind) controllerType,
                stationControllerInterface);

        // Process incoming lots, including sending lot updates over
        // RTI Connext
        controller.ProcessLots();

    } catch (string message) {
        cout << "Application exception " << message << endl;
    }


    return 0;
}


// ----------------------------------------------------------------------------
// Station controller constructor.
StationController::StationController(
        StationControllerKind kind,
        StationControllerInterface& scInterface) :
    _networkInterface(scInterface)
{
    _stationControllerKind = kind;
}

// ----------------------------------------------------------------------------
// ProcessLots:
// This method executes the main logic for the StationController:
//   1. Wait for lot status (filtered so it will only receive lots that are
//      assigned to this station controller, or that have been completed)
//   2. Update lots to say they are being processed
//   2. Process lots
//   3. Update lot status to say it is assigned to the next controller
//
void StationController::ProcessLots()
{
    dds::sub::DataReader<ChocolateLotState> reader =
        _networkInterface.ReaderChocolateLotState();
    dds::sub::cond::ReadCondition readCondition(reader,
        dds::sub::status::DataState::new_data(), [&reader, this]() {
            auto samples = reader.take();
            vector<ChocolateLotState> lotStates;
            // Copy the data so that it can be freely modified
            for (auto sample : samples) {
                lotStates.push_back(sample.data());
            }
            // --- Update lots to WAITING, or unregister completed lots ---

            // Announce that all lots I have received requests for are waiting at
            // this StationController to be processed.
            for (auto& state : lotStates) {
                UpdateState(state);
            }
            // --- Process lots ---
            // Process the lots that we know about. "Processing" a lot involves
            // just sleeping in place of real functionality
            for (auto& state : lotStates) {
                ProcessLot(state);
            }
        });

    // Create a Waitset for processing of read condition(s)
    dds::core::cond::WaitSet waitSet;
    auto wait_period = dds::core::Duration::from_millisecs(100);

    // Add the read condition to the WaitSet
    waitSet += readCondition;

    while (true) {
        // --- Wait for lots to process ---

        cout << "Station controller " 
            << StationControllerType::ControllerPrettyName(_stationControllerKind)
             << " waiting for data" << endl;

        waitSet.dispatch(wait_period);
    }
}

// ----------------------------------------------------------------------------
// UpdateState:
void StationController::UpdateState(ChocolateLotState& lotState)
{
    // Controller updating/unregistering this lot is me
    lotState.controller(_stationControllerKind);

    // --- Unregister completed lots ---
    // If this lot is entirely completed being created, I can
    // unregister it - removing any information that I was storing
    // about its state.  This means that late-joining applications will
    // not receive updates about this lot from me. If we fail to
    // unregister, the state of this lot will be available until this
    // application shuts down.
    if (lotState.lotStatus() == LotStatusKind::LOT_COMPLETED) {
        // Call to unregister lot
        _networkInterface.WriterChocolateLotState().unregister_instance(
            _networkInterface.WriterChocolateLotState().lookup_instance(lotState)
        );
        return;
    }

    // --- Update lots assigned to me to waiting state ---
    // If this lot is being assigned to me, update its status to say
    // it is waiting at my station

    // Next station is invalid until I am complete
    lotState.nextController(StationControllerKind::INVALID_CONTROLLER);

    // State is waiting at the controller
    lotState.lotStatus(LotStatusKind::WAITING_AT_SC);

    // Write this update to the network
    _networkInterface.WriterChocolateLotState().write(lotState);
}


// ----------------------------------------------------------------------------
// ProcessLot:
void StationController::ProcessLot(ChocolateLotState& lotState)
{
    // If this lot is completed, don't process it.
    if (LotStatusKind::LOT_COMPLETED == lotState.lotStatus()) {
        return;
    }

    // I am the current controller, and the current state is I am processing it
    lotState.controller(_stationControllerKind);
    lotState.lotStatus(LotStatusKind::PROCESSING_AT_SC);

    // No next controller assigned until I am done
    lotState.nextController(StationControllerKind::INVALID_CONTROLLER);

    // Write the chocolate lot state over the network
    _networkInterface.WriterChocolateLotState().write(lotState);

    // --- Query recipe for this lot ---

    // The GetRecipe() call queries recipes that are stored in the
    // middleware's queue.
    ChocolateRecipe recipe;
    bool haveRecipe = false;
    while (recipe.recipeName().empty()) {
        recipe = _networkInterface.GetRecipe(lotState.recipeName());
        if (recipe.recipeName() != lotState.recipeName()) {
            dds::core::Duration recipeWait(10, 0); // 10 s
            
            cout << "Have not received the required recipe.  Waiting for "
                 << recipeWait.sec() << " seconds for recipe." << endl;

            rti::util::sleep(recipeWait);
        }
    }

    // Get the current recipe step information to know how to
    // process the lot
    RecipeStep currentStep;

    // Start to fill in the next state of the chocolate lot based
    // on the next recipe step.
    ChocolateLotState nextState(lotState);

    // Iterate over the recipe steps
    for (auto step = begin(recipe.steps()); step != end(recipe.steps()); ++step) {
        // Iterate over the recipe until reaching the current step
        // in the process.
        if (step->stationController() == _stationControllerKind) {
            // Set currentStep to the current recipe step
            currentStep = *step;

            // If this is the last step in the recipe, we can mark
            // this lot as completed.
            if (step == end(recipe.steps())) {
                nextState.nextController(StationControllerKind::INVALID_CONTROLLER);
                nextState.lotStatus(LotStatusKind::LOT_COMPLETED);
            } else {
                nextState.nextController((++step)->stationController());
                step--;
                nextState.lotStatus(LotStatusKind::ASSIGNED_TO_SC);
            }
            break;
        }
    }

    // --- "Process" lot (really just sleep) ---
    dds::core::Duration busySleep(currentStep.seconds(), 0);

    // --- Print an update ---
    cout << "Station controller " 
        << StationControllerType::ControllerPrettyName(_stationControllerKind)
        << " processing lot #" << lotState.lotID() << " for "
        << currentStep.seconds() << " seconds" << endl;
    rti::util::sleep(busySleep);

    // --- Prepare the next state to publish ---

    // Add the ingredients from this station controller to the
    // ingredient list in this lot.

    // Add the ingredient to the list in the chocolate lot state
    nextState.ingredients().push_back(StationControllerType::ControllerIngredientName(_stationControllerKind));

    // Fill in the next controller based on the recipe we queried
    // earlier
    cout << "Station controller " << StationControllerType::ControllerIngredientName(_stationControllerKind)
         << " sending lot #" << nextState.lotID() << " to "
         << StationControllerType::ControllerPrettyName(nextState.nextController()) << endl;

    // --- Publish updated state ---
    // Update to say we are done with lot, and it is time for
    // the next station controller to process it, or that it is
    // completed.
    _networkInterface.WriterChocolateLotState().write(nextState);
}

// ----------------------------------------------------------------------------
// PrintHelp:
// Function that prints out the help if somebody runs the application with
// --help
//
void PrintHelp()
{
    cout << "Valid options are: " << endl;
    cout << "    --controller-type [number]"
         << " Valid values 1-5. Type of controller this app " << endl
         << "                               "
         << "represents" << endl;
    cout << "    --no-multicast"
         << "             Do not use multicast "
         << "(note you must edit XML" << endl
         << "                               "
         << "configuration to include IP addresses)" << endl;
}
