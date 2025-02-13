all:
	g++ -o BankAccount main.cpp BankAccount.cpp

run: all
	./BankAccount

clean:
	rm -f BankAccount