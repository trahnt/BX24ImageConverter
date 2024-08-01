all:
	g++ BX24Convert.cpp -o convert `pkg-config --cflags --libs opencv4`

clean:
	rm convert