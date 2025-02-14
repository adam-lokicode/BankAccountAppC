Steps to Implement

1. Use ANTITHESIS_ASSERT to ensure the withdrawal amount is positive.

2. Use ANTITHESIS_RANDOM(int) to generate a random withdrawal amount.

3. Use antithesis_lifecycle_event("event") to track transaction start and completion.

clang++ -o BankAccount.o -c BankAccount.cpp
clang++ -o BankAccount_executable BankAccount.o
./BankAccount_executable

Recall that the basic SDK workflow is

Include the C++ header file.
Use SDK functions in your code.
Compile and link your code.
Deploy your build.

clang++ \
 -I /Users/adamtoth/Documents/GitHub/antithesis-sdk-cpp \
 -std=c++20 \
 -fsanitize-coverage=trace-pc-guard \
 -g \
 -o BankAccount.o \
 -c BankAccount.cpp

🛠 C++ Implementation Questions

1. How does ANTITHESIS_ASSERT() help catch bugs?

2. Why did we use ANTITHESIS_RANDOM(int) % 150 for withdrawals?

3. How do antithesis_lifecycle_event() calls improve debugging?

4. If a test keeps failing at the assertion, how would you debug it?

5. What would happen if we didn’t use assertions in the BankAccount class?
