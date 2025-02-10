#!/bin/sh

# Set session name
SESSION="OtelAdapter"
SESSIONEXISTS=$(tmux list-sessions | grep $SESSION)

# Only create tmux session if it doesn't already exist
if [ "$SESSIONEXISTS" = "" ]
then
    # Start new session with our name
    tmux new-session -d -s $SESSION

    # Name first pane and start the routing service
    tmux rename-window -t 0 'Routing Service'
    tmux send-keys -t 'Routing Service' 'rtiroutingservice -cfgFile ./RsTelemetryGateway.xml -cfgName "OpenTelemetryGateway"' C-m 'clear' C-m

    # Create and setup pane for generator
    tmux new-window -t $SESSION:1 -n 'Metrics Generator'
    tmux send-keys -t 'Metrics Generator' './generator -d 2 -q generator_qos.xml' C-m
fi

# Attach session, on the main window
tmux attach-session -t $SESSION:0
