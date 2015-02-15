/**
* @requires  >= 1
* @param nn The starting parameter.
* @return The number of Collatz calls needed to reach 1 from the parameter .
*         This implementation is iterative to avoid stack overflows
*/
template <typename T>
T CollatzCount(T nn) {
        T ONE("1");   T TWO("2");   T THREE("3");
        
        T result("1");
        for (;!(nn==ONE);result=result+ONE) {
                if (TWO*(nn/TWO)==nn) // i.e. nn is even
                nn = nn/TWO;
                else                  // i.e. nn is odd
                nn = THREE*nn+ONE;
        }
        return result;
}