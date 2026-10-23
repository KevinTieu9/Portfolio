package org.example;

import static org.example.TrafficLight.State.*;
import static org.example.TrafficLight.Event.TIMER_EXPIRES;

/**
 * Main.java
 * Simple driver that cycles the traffic light FSM.
 * Author: Kevin Tieu
 */
public class Main {
    /**
     * Start the program. Cycle the light six times with a two-second pause.
     *
     * args - command-line arguments (unused)
     */
    public static void main(String[] args) throws InterruptedException {
        TrafficLight.State current = RED;
        int cycles = 6;

        System.out.println("Traffic light FSM (timer-driven cycle)");
        System.out.println("--------------------------------------");

        for (int i = 0; i < cycles; i++) {
            System.out.println("State: " + TrafficLight.stateName(current));
            Thread.sleep(2000); // 2-second pause between transitions
            current = TrafficLight.transition(current, TIMER_EXPIRES);
        }

        System.out.println("Finished.");
    }
}
