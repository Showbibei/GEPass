cmake_minimum_required(VERSION 2.6)
project(MYENGINE)

string(TOLOWER "${CMAKE_CXX_COMPILER_ID}" COMP)
string(TOLOWER "${CMAKE_SYSTEM_NAME}" PLATFORM)
string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" ARCH)
message("${COMP}-${PLATFORM}-${ARCH}")

add_definitions(-DSDL_MAIN_HANDLED)

include_directories(
  src
  ${PROJECT_SOURCE_DIR}/contrib/common
  ${PROJECT_SOURCE_DIR}/contrib/${COMP}-${PLATFORM}-${ARCH}/include
)

link_directories(
  ${PROJECT_SOURCE_DIR}/contrib/${COMP}-${PLATFORM}-${ARCH}/lib
)

if(MINGW)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s -static")
  add_definitions(-DGLEW_STATIC)
  set(STATIC_LIBS imm32 iconv winmm ole32 gdi32 oleaut32 version)
  set(LIBGLEW glew32)
  set(LIBSDL2 SDL2)
elseif(MSVC)
  add_definitions(-DGLEW_STATIC)
  set(STATIC_LIBS imm32 winmm setupapi version)
  set(LIBGLEW glew32s)
  set(LIBSDL2 SDL2-static)
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2")
endif()

add_library(rend
  src/rend/Exception.cpp
  src/rend/Context.cpp
  src/rend/Texture.cpp
  src/rend/RenderTexture.cpp
  src/rend/Shader.cpp
  src/rend/Buffer.cpp
  src/rend/Mesh.cpp
  src/rend/Util.cpp
  src/rend/stb_image.cpp
)
if(MSVC OR MINGW)
  target_link_libraries(rend ${LIBGLEW} opengl32)
else()
  target_link_libraries(rend GLEW GL)
endif()

add_library(myengine
  src/myengine/Core.cpp
  src/myengine/Entity.cpp
  src/myengine/Component.cpp
  src/myengine/Exception.cpp
  src/myengine/Renderer.cpp
  src/myengine/Transform.cpp
  src/myengine/Keyboard.cpp
  src/myengine/Camera.cpp
  src/myengine/Asset.cpp
  src/myengine/AssetManager.cpp
  src/myengine/Material.cpp

  src/myengine/Model.cpp

  src/myengine/Audio.cpp
  src/myengine/AudioSource.cpp
  src/myengine/BoxCollider.cpp
  src/myengine/RigidBody.cpp

  src/myengine/Camera.h
  src/myengine/Core.h
  src/myengine/Entity.h
  src/myengine/Component.h
  src/myengine/Exception.h
  src/myengine/Renderer.h
  src/myengine/Transform.h
  src/myengine/Keyboard.h
  src/myengine/myengine.h
  src/myengine/Asset.h
  src/myengine/AssetManager.h
  src/myengine/Material.h

  src/myengine/Model.h

  src/myengine/Audio.h
  src/myengine/AudioSource.h
  src/myengine/BoxCollider.h
  src/myengine/RigidBody.h


)


if(MSVC OR MINGW)
  target_link_libraries(myengine rend ${LIBSDL2} ${STATIC_LIBS} openal32)
else()
  target_link_libraries(rend GLEW GL AL)
endif()

add_executable(demo
  src/demo/main.cpp
)
target_link_libraries(demo myengine)

