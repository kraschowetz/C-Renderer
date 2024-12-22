#include "core/engine.h"

int main() {
	Engine *engine = create_engine();
	
	engine_start(engine);

	return 0;
}
