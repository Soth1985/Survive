#include <Survive/application.h>

#include <Survive/collision/intersection_tests.h>

int main()
{
	Survive::IntersectionTests::Tests();

	Survive::Application app;
	app.Run();
	return 0;
}
