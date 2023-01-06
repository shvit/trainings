# Implementation quick sort algorithm into STL vector.

Also has sorted statistics:
- Algorithm stage count (deep)
- Count of swaps

Construct from initializer list or from string with space-separated numbers.

Has unit-tests

## Build application qsort

<pre>
make
</pre>

How use:

<pre>
./qsort 9 8 7 6 5
Parsed input array with 5 items
Source: 9 8 7 6 5 
Result: 5 6 7 8 9 
Sorting statistics:
  Maximum deep: 1
  Swap count: 2
</pre>

or

<pre>
./qsort
Enter array data (separated by Space and finish with Enter):
4 3 2 1 0
Parsed input array with 5 items
Source: 4 3 2 1 0 
Result: 0 1 2 3 4 
Sorting statistics:
  Maximum deep: 1
  Swap count: 2
</pre>


## Run unit tests

<pre>
make check
</pre>