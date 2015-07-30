#### Period detection of a Pseudorandom Number Generator

A pseudorandom natural number generator is a function that generates a sequence of R0, R1, R2, ... of natural numbers with 
randomness characteristics according to some criteria. In its general form, such a generator is in the form

![Ri](https://github.com/GeorgePapageorgakis/random-number-generator-period-detection/blob/master/Ri.jpg)

and f an integral function. In practice we want the numbers to be smaller than an upper limit, ie 0 ≤ Ri ≤ m, so we start 
with selecting a suitable m and a function f(x) such that 0 ≤ f(x) < m, where 0 ≤ x < m.

A generator based on such a function is ultimately periodic, ie from a point and then repeats the same series of numbers. 
This, in mathematical terms, means that there are two numbers μ and λ, such that the values ​​of the sequence 

![R.](https://github.com/GeorgePapageorgakis/random-number-generator-period-detection/blob/master/Ri2.jpg)

The purpose is to detect the period of a pseudorandom number generator. More specifically, given a linear generator remainder,
it produces consecutive numbers of the sequence and as soon as it finds the first value that is equal to a previous value, it 
stops and returns the number of steps intervening between these two same values. A key feature in this technique is to determine
whether the current value of the sequence is equal to one of the values that have been previously appeared.

The method used for the implementation of the hash table, is referred to as Fragmentation Chain.