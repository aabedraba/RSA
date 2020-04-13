# Implementación del algoritmo RSA
From obtaining the prime numbers, creating private-public keys to a per-block encryption, this is a ground-up full implementation of the RSA cryptosystem in C++ without any additional library except for [GnuMP](https://gmplib.org/), for managing numbers in the order of 2^2048.

**Dependecies:**

* cmake >= 3.5: `apt-get install cmake`
* gmp: `sudo apt install libgmp3-dev`

**To compile:**

```bash
$ cd build/
$ cmake ..
$ make
```
And execute with  `./RSA`

**Docker alternative**

If you don't wish to compile and/or download the dependencies, you can use a Docker image that I've prepared (yes, unnecesary, I know). You have to have installed [Docker](https://www.docker.com/community-edition), of course, and then in the repository directory type the following commands:

```bash
$ docker build . -t rsabinary
$ docker run -ti rsabinary
```

## Design
I use three different classes explained here:

### PrimeNumbers
This class concerns only the generation of prime numbers with desired length that will then be used to obtain the public-private keys. Normally we use prime numbers in the order of 1024bits.

To check if a number is prime, we should check if the number isn't divisible by all smaller prime numbers. So, in theory, we would have to save all these smaller prime numbers. But as we're working with numbers in the order of 1024bit (approx. 700 digits) saving all the prime numbers in this order in a hard disk would make a black hole collapse.  

So, the fastest (and safest for the universe) way is to make a probabilistic verification, instead of deterministic, to check if the number could be a possible prime number.

For that I decided to use the [**Miller-Rabin**](https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test) primality test, that **increases** to an acceptable magnitude the probablity of a number not being prime. Nevertheless, this test is hard on CPU and thus runs slowly, so we should use it as little as possible. 

So, to reduce the number of uses of the Miller-Rabin test, we first "manually" check if the random number chosen is not divisible by all the prime number in the range of [2, 1000]. By doing that, we are increasing the probabity of being prime to 90% (see [Prime Number Theorem](https://en.wikipedia.org/wiki/Prime_number_theorem)). So, with that done, we can procede to use the Miller-Rabin primality test, making the process way more efficient. 

Now, the Miller-Rabin primailty test reduces the probablity in the order of 4^-k, with `k` being the number of iterations of the test. So, starting from 90%, with 10 iterations we would have a **99.9999915736%** chance of being a prime random number. Enough.

### Keys
The `Keys`class has the trivial implementation of public-private key generation for RSA.

1. We need two numbers for the public Key: `(e, n)` 
* `n = p*q`, being `p and k` two prime numbers.
* `e` has been chosen to be the number 65573, known as [Fermat's prime number](https://en.wikipedia.org/wiki/Fermat_number) as its binary representation is `10000000000000001` which makes it very suitable for efficient binary operations. And given it's a prime number, when we need to obtain our original `p` and `q` from the private key the process would be trivial, as we already have one of the coprimes we save the check.
2. For our private key we need another two numbers `(d, e)`
* `d = e^-1 mod carmichael`
* `carmichael` = `(p-1)(q-1)`
  * Carmichael is know as the [Phi Function](https://en.wikipedia.org/wiki/Carmichael_function), by Robert Carmichael.

`e^-1 mod carmichael` requires the [*Euclidian Algorithm*](https://en.wikipedia.org/wiki/Euclidean_algorithm) which requires recursion and GnuMP doesn't support that, so I used a method from the library. 