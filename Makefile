all: convert
	
convert: BX24Convert.cpp
	g++ BX24Convert.cpp -o convert `pkg-config --cflags --libs opencv4`

clean:
	rm -f convert

clear:
	rm -f *.jpg *.png