#!/bin/bash

# The executable for this benchmark
BENCHMARK_EXE=$HOME/Code/ply-parsing-perf/build-release/ply-parsing-perf

# Directories containing the model collections that we'll run the benchmark on.
COLLECTIONS="$HOME/Models/pbrt-v3-scenes $HOME/Models/benedikt-bitterli $HOME/Models/Stanford3DScans"

# Directory we'll write the detailed benchmark results to
RESULTS_DIR=$HOME/Code/ply-parsing-perf/results-macos

# Run the detailed benchmarks for each of the model collections
echo "Running detailed benchmarks..."
for COLLECTION in $COLLECTIONS ; do
  cd $COLLECTION
  COLLECTION_NAME=`basename $COLLECTION`
  echo "  $COLLECTION_NAME:" $BENCHMARK_EXE --transposed --slowdown --quiet                allplyfiles.txt -o $RESULTS_DIR/$COLLECTION_NAME.md
  $BENCHMARK_EXE --transposed --slowdown --quiet                allplyfiles.txt -o $RESULTS_DIR/$COLLECTION_NAME.md
  echo "  $COLLECTION_NAME:" $BENCHMARK_EXE --transposed --slowdown --quiet --precognition allplyfiles.txt -o $RESULTS_DIR/$COLLECTION_NAME--precog.md
  $BENCHMARK_EXE --transposed --slowdown --quiet --precognition allplyfiles.txt -o $RESULTS_DIR/$COLLECTION_NAME--precog.md
done

# Running summary benchmarks for each of the collections
echo "Generating summary benchmarks..."
cd $RESULTS_DIR

echo "| Collection        | # files |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |" > summary.md
echo "| :---------------- | ------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |" >> summary.md

echo "| Collection        | # files |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |" > summary--precog.md
echo "| :---------------- | ------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |" >> summary--precog.md

for COLLECTION in $COLLECTIONS ; do
  COLLECTION_NAME=`basename $COLLECTION`
  NUM_FILES=`cat $COLLECTION/allplyfiles.txt | wc -l`
  SUMMARY_LINE=`tail -1 $COLLECTION_NAME.md | cut -d '|' -f 3-`
  SUMMARY_LINE_PRECOG=`tail -1 $COLLECTION_NAME--precog.md | cut -d '|' -f 3-`

  # echo "Collection: $COLLECTION_NAME"
  # echo "  NUM_FILES           = $NUM_FILES"
  # echo "  SUMMARY_LINE        = $SUMMARY_LINE"
  # echo "  SUMMARY_LINE_PRECOG = $SUMMARY_LINE_PRECOG"
  printf "| %-17s | %7d |%s\n" "$COLLECTION_NAME" "$NUM_FILES" "$SUMMARY_LINE" >> summary.md
  printf "| %-17s | %7d |%s\n" "$COLLECTION_NAME" "$NUM_FILES" "$SUMMARY_LINE_PRECOG" >> summary--precog.md
done
echo "Done."
