# Allan Deviation C Tools 

This is a light collection of C functions, to compute Allan variances & related statistics.

These statistics are used in several fields & situations:

+ to measure & study the stability of a signal over time

+ compare a signal to a reference signal

+ Study the stability & behavior of sensors like a Gyroscope (angle sensor) and Accelerometer (g sensor)

against time (transfer function over time)

## Learn from this project

+ How to compute the Allan variance and other modern flavors 
  + like MDEV: Modified Allan Deviation
  + OADEV: Overlapped Allan Deviation
+ Determine which variance to use and why, depending on the situation
+ Analyze & use a variance plot (variance against time constants)

## Documentation

Refer to the project documentation:

```bash
xpdf allan-dev-c-tools/doc/documentation.pdf
```

## Getting started

```bash
TODO
```

Run the test / benchmarks

```
make -C allan-dev-c-tools/tests
```