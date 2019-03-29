#include "Df1.h"
#include "Df1Serial.h"



int main(int argc, char* argv[]) {
	for (const auto items : getAvailablePorts()) {
		printf("%s\n", items);
	}
}
