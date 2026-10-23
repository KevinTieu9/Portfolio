package org.example;

/**
 * TrafficLight.java
 * Personal project — Traffic Light
 *
 * Author: Kevin Tieu
 *
 * States and transitions (timer-driven cycle):
 *   RED    + TIMER_EXPIRES -> GREEN
 *   GREEN  + TIMER_EXPIRES -> YELLOW
 *   YELLOW + TIMER_EXPIRES -> RED
 *
 * Any other event leaves the current state unchanged.
 */
public class TrafficLight {

    /** Possible light states. */
    public enum State {
        RED, GREEN, YELLOW
    }

    /** Events that can drive a transition. */
    public enum Event {
        TIMER_EXPIRES
    }

    /**
     * Returns the printable name of a state.
     * @param state the current state
     * @return the state name (e.g., "RED")
     */
    public static String stateName(State state) {
        return state.name();
    }

    /**
     * Computes the next state given the current state and an event.
     * Only TIMER_EXPIRES produces a change; all other events are ignored.
     *
     * @param current the present state
     * @param event   the event that just occurred (may be null)
     * @return the resulting state
     */
    public static State transition(State current, Event event) {
        // Guard: ignore anything that is not a timer expiry
        if (event != Event.TIMER_EXPIRES) {
            return current;
        }

        // Timer-driven cycle
        return switch (current) {
            case RED    -> State.GREEN;
            case GREEN  -> State.YELLOW;
            case YELLOW -> State.RED;
        };
    }
}
