// Demo file with intentional style and performance issues that cppcheck reports
// (severity "style" / "performance"). The code compiles and runs correctly,
// it is just poorly written. Do NOT use this code as an example.
#include <cstdio>
#include <string>
#include <vector>

// 1. Constructor with one argument is not explicit (noExplicitConstructor)
// 2. Member not initialized in the constructor (uninitMemberVar)
class Counter {
public:
    Counter(int start) : value(start) {}

    int get() const { return value; }

private:
    int value;
    int step;
};

// 3. Large object passed by value instead of const reference (passedByValue)
std::size_t countLongNames(std::vector<std::string> names) {
    std::size_t count = 0;
    // 4. Raw loop that could be a standard algorithm (useStlAlgorithm)
    for (const std::string& name : names) {
        if (name.size() > 5) {
            count++;
        }
    }
    return count;
}

// 5. Variable assigned but never used (unreadVariable)
// 6. Variable scope can be reduced (variableScope)
int scale(int input) {
    int unused = input * 2;
    int result;
    if (input > 0) {
        result = input * 10;
        return result;
    }
    return 0;
}

// 7. Same expression on both sides of an operator (duplicateExpression)
bool isSame(int a) {
    return a == a;
}

// 8. Condition is always false (knownConditionTrueFalse)
int limit() {
    int max = 10;
    if (max > 100) {
        return 100;
    }
    return max;
}

// 9. Initial value is overwritten before it is read (redundantInitialization)
int twice(int a) {
    int r = a;
    r = a * 2;
    return r;
}

// 10. C-style pointer cast (dangerousTypeCast, invalidPointerCast)
int truncate(double value) {
    const double* p = &value;
    const int* asInt = (const int*)p;
    return *asInt != 0 ? static_cast<int>(value) : 0;
}

// 11. Local variable shadows an outer one (shadowVariable)
int sumTwice(int total) {
    int sum = 0;
    for (int i = 0; i < 2; ++i) {
        int sum = total;
        std::printf("%d\n", sum);
    }
    return sum;
}

int main() {
    Counter c = 5;
    std::vector<std::string> names = {"alpha", "bravo-long", "charlie-long"};
    std::printf("%d %zu %d %d %d %d %d %d\n", c.get(), countLongNames(names), scale(3),
                isSame(1), limit(), twice(2), truncate(1.5), sumTwice(4));
    return 0;
}
