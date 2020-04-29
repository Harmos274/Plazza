SHD_PATH	?=	.

SHD_INCLUDE				=	-I ${SHD_PATH}/include
SHD_INCLUDE_PRIVATE		=	${SHD_INCLUDE} -I ${SHD_PATH}/include/shd

SHD_CXXFLAGS		=	${SHD_INCLUDE_PRIVATE}
SHD_CXXFLAGS_TESTS	=	${SHD_CXXFLAGS} --coverage

ifeq (GUI, ${findstring GUI,${SHD_MODULES}})
SHD_SRC				+=	src/imgui/imgui.cpp				\
						src/imgui/imgui-SFML.cpp		\
						src/imgui/imgui_draw.cpp		\
						src/imgui/imgui_widgets.cpp		\
						src/gui/ImGuiRenderWindow.cpp

SHD_INCLUDE			+=	-I ${SHD_PATH}/include/imgui

override LDFLAGS	+=	-lsfml-graphics -lsfml-window -lsfml-system -lOpenGL
endif

ifeq (THREADPOOL, $(findstring THREADPOOL,${SHD_MODULES}))
SHD_SRC				+=	src/threadpool/Worker.cpp		\
						src/threadpool/JobQueue.cpp		\
						src/threadpool/ThreadPool.cpp

SHD_SRC_TESTS		+=	tests/threadpool/Worker.cpp			\
						tests/threadpool/JobQueue.cpp		\
						tests/threadpool/ThreadPool.cpp		\
						tests/threadpool/Job.cpp

override LDFLAGS	+=	-lpthread
endif

SHD_SRC_TESTS		+=	tests/WordIterator.cpp

SHD_OBJ				=	$(addprefix ${SHD_PATH}/, ${SHD_SRC:.cpp=.o})
SHD_OBJ_TESTS		=	$(addprefix ${SHD_PATH}/, ${SHD_SRC_TESTS:.cpp=.o})

ifdef CXX_LOG

$(SHD_OBJ):			${SHD_PATH}/%.o: ${SHD_PATH}/%.cpp
	@echo -e "${CXX_LOG}"
	@${CXX} -c -o $@ $< ${CXXFLAGS} ${SHD_CXXFLAGS}

$(SHD_OBJ_TESTS):	${SHD_PATH}/%.o: ${SHD_PATH}/%.cpp
	@echo -e "${CXX_LOG}"
	@${CXX} -c -o $@ $< ${CXXFLAGS} ${SHD_CXXFLAGS_TESTS}

else

$(SHD_OBJ):			%.o:	%.cpp
	${CXX} -c -o $@ $< ${CXXFLAGS} ${SHD_CXXFLAGS}

$(SHD_OBJ_TESTS):	%.o:	%.cpp
	${CXX} -c -o $@ $< ${CXXFLAGS} ${SHD_CXXFLAGS_TESTS}
endif

