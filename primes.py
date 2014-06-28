from math import ceil, sqrt
from bisect import bisect

primes = [1, 2, 3]

def isPrime(number):
	for x in range(2, bisect(primes, ceil(sqrt(number)))):
		if (number % primes[x] == 0):
			return
	primes.append(number)
	return

for i in range(5, 1000000, 2):
	isPrime(i)
					
# print "primes: " + str(primes)
print "Number of primes: " + str(len(primes))
