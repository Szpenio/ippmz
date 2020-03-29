#!/bin/bash

# USAGE:
# Script testing programme PROG,
# comparing its output files with those found in direction DIR

if [ $# != 2 ]
then
  echo "Usage: $0
  <programme name>
  <direction where input and proper output can be found>." >&2
  exit 1
fi

PROG=$1
DIR=$2

countOUT=0
countERR=0
countMEM=0

echo "Odpalam $PROG na plikach *.in z folderu $DIR"

OUT=$(mktemp $DIR/out.XXXXX)
ERR=$(mktemp $DIR/err.XXXXX)

time for f in $(ls $DIR/*.in)
do
  echo "$f:"
  ./$PROG <$f 1>$OUT 2>$ERR
  if diff ${f%in}out $OUT >/dev/null 2>&1
  then
    echo "OUT OK"
  else
    echo "OUT WRONG"
    countOUT++
  fi
  if diff ${f%in}err $ERR >/dev/null 2>&1
  then
    echo "ERR OK"
  else
    echo "ERR WRONG"
    countERR++
  fi
  valgrind --error-exitcode=15 --leak-check=full --show-leak-kinds=all \
  --errors-for-leak-kinds=all ./$PROG <$f >/dev/null 2>&1
  if [ $? ]
  then
    echo "MEMORY OK"
  else
    echo "MEMORY PROBLEM"
    countMEM++
  fi
done

echo "Liczba niezgodnych plików .out: $countOUT"
echo "Liczba niezgodnych plików .err: $countERR"
echo "Liczba problemów z pamięcią: $countMEM"


rm $DIR/err* $DIR/out*
