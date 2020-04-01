# Observer Pattern
The Observer Pattern defines a one-to-many dependency between objects so that when one object changes state, 
all of its dependents are notified and updated automatically.

## Design principle:
Strive for loosely coupled designs between objects that interact.
Loosely coupled designs allow us to build flexible OO systems that can handle change because they minimize
the interdependency between objects.

## Benefits of Observer design pattern
1. It provides an object design where subjects and observers are loosely coupled
2. The only thing the subject knows about an observer is that it implements a certain interface (the Observer interface).
3. We can add new observers or remove old observers at any time.
4. We never need to modify the subject to add new types of observers.
5. We can reuse subjects or observers independently of each other.
6. Changes to either the subject or an observer will not affect the other


