#include <memory>
#include <fstream>
#include <iostream>
#include <vector>

#include "ExampleBrowser.h"

#include "vel/MeshLoaderInterface.h"
#include "vel/AssimpMeshLoader.h"
#include "vel/Log.h"

#include "E1.h"
#include "E2.h"

#include "glm/gtx/string_cast.hpp"

#include "nlohmann/json.hpp"
using json = nlohmann::json;



int main()
{
	vel::Config conf = vel::Config();
	conf.APP_EXE_NAME = "vel3d_examples.exe";
	conf.APP_NAME = "Vel3D_Examples";
	conf.LOGIC_TICK = 60.0f;
	conf.CURSOR_HIDDEN = true;
	conf.USE_IMGUI = false;
	conf.OPENGL_DEBUG_CONTEXT = false;

	std::unique_ptr<vel::Window> w = std::make_unique<vel::Window>(conf);
	std::unique_ptr<vel::GPU> gpu = std::make_unique<vel::GPU>(conf.FXAA);
	std::unique_ptr<vel::MeshLoaderInterface> ml = std::make_unique<vel::AssimpMeshLoader>();
	std::unique_ptr<vel::AssetManager> am = std::make_unique<vel::AssetManager>(conf.DATA_DIR, std::move(ml), gpu.get());

	// Bootstrap an App
	std::unique_ptr<ExampleBrowser> app = std::make_unique<ExampleBrowser>(conf, w.get(), gpu.get(), am.get());

	// Load Scenes into memory (multiple or just one), set one to active
	app->addScene(std::move(std::make_unique<E2>(conf.DATA_DIR)));
	app->addScene(std::move(std::make_unique<E1>(conf.DATA_DIR)), true);

	// Run the engine (blocking main thread)
	app->execute();



	//system("pause");
	return 0;
}

