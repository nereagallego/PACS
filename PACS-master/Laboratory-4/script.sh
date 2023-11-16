for i in 1 2 4 8 16 32 64 128
do
  for j in {1..10}
  do
    ./smallpt_thread_pool $i $i
  done
done