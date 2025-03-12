#!/bin/sh

# Set session name
SESSION="OtelAdapter"
SESSIONEXISTS=$(tmux list-sessions | grep $SESSION)

# Only create tmux session if it doesn't already exist
if [ "$SESSIONEXISTS" = "" ]
then
    # Start new session with our name
    tmux new-session -d -s $SESSION

    tmux rename-window "Routing Service"

    # Split the window into two horizontal panes (top and bottom)
    tmux split-window -v

    # Setup pane for Prometheus Gateway (pane 0)
    tmux select-pane -t 0
    tmux select-pane -T "Routing-Service"
    tmux send-keys 'rtiroutingservice -cfgFile ./RsTelemetryGateway.xml -cfgName "OpenTelemetryGateway"' C-m 'clear' C-m

    # Create and setup pane for Generator
    tmux select-pane -t 1
    tmux select-pane -T "Gateway"
    tmux send-keys './generator -d 2 -q generator_qos.xml' C-m
fi

# Attach session, on the main window
tmux attach-session -t $SESSION:0
