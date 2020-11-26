if ! [ -f profiler_berdash.out ]
then 
	g++ profiler.cpp -o "profiler_berdash.out"
fi
./profiler_berdash.out
python3 graph.py
