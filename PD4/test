#!/bin/bash

FLAG=0

for i in *.in; do
  case "$1" in
    "cpp" | "c")
      diff -q -i -E -w -B -a -s <(./main < $i) <(cat ${i//\.in/.out})
      ;;

    "py")
      diff -q -i -E -w -B -a -s <(python main.py < $i) <(cat ${i//\.in/.out})
      ;;

    *)
      FLAG=1
      ;;
  esac
done

if [ $FLAG -eq 1 ]; then
  echo "Specify laguage: c, cpp, py"
fi
