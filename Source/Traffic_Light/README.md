# Traffic Light Finite State Machine (Java + JUnit 5)

**Author:** Kevin Tieu

A direct Java port of the earlier C traffic-light FSM, with matching unit tests.

## Behavior
- RED + TIMER_EXPIRES → GREEN
- GREEN + TIMER_EXPIRES → YELLOW
- YELLOW + TIMER_EXPIRES → RED
- Any other event leaves the state unchanged

## Build and test
Requires a JDK (17+) and Maven.

```bash
mvn test
```

## Run the driver
```bash
mvn compile exec:java -Dexec.mainClass="org.example.Main"
```

Or open the project in IntelliJ IDEA and run `Main` or the tests directly.
