package org.example;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.example.TrafficLight.State.*;
import static org.example.TrafficLight.Event.TIMER_EXPIRES;

/**
 * TrafficLightTest.java
 * Personal project — Traffic Light
 *
 * Author: Kevin Tieu
 *
 * Tests were written first (TDD style) and then the transition logic
 * was implemented to satisfy them.
 */
class TrafficLightTest {

    /**
     * RED + timer expires must become GREEN.
     */
    @Test
    void redTimerExpiresGoesToGreen() {
        assertEquals(GREEN, TrafficLight.transition(RED, TIMER_EXPIRES));
    }

    /**
     * GREEN + timer expires must become YELLOW.
     */
    @Test
    void greenTimerExpiresGoesToYellow() {
        assertEquals(YELLOW, TrafficLight.transition(GREEN, TIMER_EXPIRES));
    }

    /**
     * YELLOW + timer expires must become RED.
     */
    @Test
    void yellowTimerExpiresGoesToRed() {
        assertEquals(RED, TrafficLight.transition(YELLOW, TIMER_EXPIRES));
    }

    /**
     * An unrecognized event (represented here by null) must leave the
     * state unchanged.
     */
    @Test
    void unknownEventLeavesStateUnchanged() {
        assertEquals(RED, TrafficLight.transition(RED, null));
    }
}
