--*****************************************************************************
--*    (c) 2005-2013 Copyright, Real-Time Innovations, All rights reserved.   *
--*                                                                           *
--*         Permission to modify and use for internal purposes granted.       *
--* This software is provided 'as is', without warranty, express or implied.  *
--*                                                                           *
--*****************************************************************************


--
-- A script that increments and decrements a "Temperature" value, and if it
-- is outside of certain parameters generates an "Alarm" value of too hot or
-- too cold.
--

--
-- Interface of the component: two outputs of Alarm and Temperature
-- 
-- The Temperature is written periodically.  To support this, the QoS in the 
-- .xml file is BEST_EFFORT.
--
-- The Alarm is written only when the temperature goes above or below 
-- certain threshholds.
-- To support a pattern of Alarm data that only changes when the Alarm state
-- changes, the QoS in the .xml file is tuned for Occasionally-Changing State 
-- Data.
--
-- In this case, we have a simple system where the RTI Connext DDS Topics
-- are known in advance and unchanging.  Because of this, we can access 
-- the DataWriters explicitly by name.  To decouple the Topic from the 
-- data, you can use the position of the DataWriter in the queue to look 
-- it up, instead of knowing the Topic name in advance.


local TemperatureWriter = CONTAINER.WRITER['Publisher::TemperatureWriter']
local AlarmWriter = CONTAINER.WRITER['Publisher::AlarmWriter'] 
local Alarm = AlarmWriter.instance


-- Global values:
-- We have several global variables, to support this use case.  Global
-- variables are saved across invocations of the script, so they maintain their
-- values every time this is run.
if not TEMPERATURE then 
	TEMPERATURE = {['previous'] = 0, ['low'] = 32, ['high'] = 100} 
	APPID = 234 
	-- These must be created explicitly because there is no mapping from an 
	-- enumeration in the IDL file to the values in this Lua script.
    ALARM_LEVEL= {['WARNING']  = 0,
				  ['ERROR'] = 1}
	ALARM_KIND = {['TOO_COLD'] = 0,
				  ['TOO_HOT'] = 1 }
	INCREMENT = 1
	INITIAL_VALUES = 1
end

-- The current temperature is a local value
local current 

	
if (TEMPERATURE['previous'] == 120) then
	INCREMENT = -1
end

if (TEMPERATURE['previous'] == 0) then 
	INCREMENT = 1
end

-- Temperature is either increasing or decreasing depending on whether this
-- has crossed a threshhold
current = TEMPERATURE['previous'] + INCREMENT

-- Set up the values for the Temperature and Alarm DataWriters
TemperatureWriter.instance['value'] = current
TemperatureWriter.instance['appID'] = APPID
AlarmWriter.instance['appID'] = APPID

-- Write the temperature value
TemperatureWriter:write()

-- If the temperature has just gone below the low threshhold
-- send an Alarm with level "warning"
if ( current < TEMPERATURE['low'] and 
	(TEMPERATURE['previous'] >= TEMPERATURE['low']
	or INITIAL_VALUES == 1)) then
	Alarm['alarmType'] = ALARM_LEVEL['WARNING']
	Alarm['alarmLevel'] = ALARM_KIND['TOO_COLD']
	INITIAL_VALUES = 0
	AlarmWriter:write()
end

-- If the temperature has just gone above the high threshhold
-- send an Alarm with level "error"
if (current > TEMPERATURE['high'] and 
	(TEMPERATURE['previous'] <= TEMPERATURE['high']
	or INITIAL_VALUES == 1)) then
	Alarm['alarmType'] = ALARM_LEVEL['ERROR']
	Alarm['alarmLevel'] = ALARM_KIND['TOO_HOT']
	INITIAL_VALUES = 0
	AlarmWriter:write()
end


-- If the temperature has gone back to normal, unregister the 
-- Alarm data because there are no outstanding alarms
if ((current > TEMPERATURE['low'] and current < TEMPERATURE['high']) and
	(TEMPERATURE['previous'] <= TEMPERATURE['low'] 
			or TEMPERATURE['previous'] >=  TEMPERATURE['high'])) 
then
	AlarmWriter:unregister()
end

-- Set the global previous value of temperature
TEMPERATURE['previous']  = current
