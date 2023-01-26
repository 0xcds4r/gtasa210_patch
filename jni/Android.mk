ifeq ($(TARGET_ARCH_ABI), arm64-v8a)
	LOCAL_PATH := $(call my-dir)

	include $(CLEAR_VARS)

	LOCAL_MODULE := GTASAPatch
	LOCAL_LDLIBS := -lm -llog -lc -lz -ljnigraphics -landroid -lEGL -lGLESv2 -lOpenSLES

	LOCAL_C_INCLUDES += $(wildcard $(LOCAL_PATH)/../deps/)
	FILE_LIST += $(wildcard $(LOCAL_PATH)/../deps/*/*.cpp)
	FILE_LIST += $(wildcard $(LOCAL_PATH)/../deps/*/*.c)
	LOCAL_C_INCLUDES += $(wildcard $(LOCAL_PATH)/../src/)
	FILE_LIST += $(wildcard $(LOCAL_PATH)/../src/*.cpp)
	FILE_LIST += $(wildcard $(LOCAL_PATH)/../src/*.c)

	LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

	LOCAL_CFLAGS += -w
	LOCAL_CFLAGS += -s
	LOCAL_CFLAGS += -fvisibility=default
	LOCAL_CFLAGS += -fpack-struct=1
	LOCAL_CFLAGS += -fexceptions
	LOCAL_CFLAGS += -pthread
	LOCAL_CFLAGS += -Wall
	LOCAL_CFLAGS += -O2
	LOCAL_CFLAGS += -DNDEBUG
	LOCAL_CFLAGS += -DHOST_ENDIAN_IS_LITTLE
	LOCAL_CFLAGS += -DLITTLE_ENDIAN
	LOCAL_CFLAGS += -D_ARM_
	LOCAL_CFLAGS += -std=c11
	LOCAL_CPPFLAGS += -std=c++14

	include $(BUILD_SHARED_LIBRARY)
else
	LOCAL_PATH := $(call my-dir)

	include $(CLEAR_VARS)

	LOCAL_MODULE := GTASAPatch
	LOCAL_LDLIBS := -lm -llog -lc -lz -ljnigraphics -landroid -lEGL -lGLESv2 -lOpenSLES

	LOCAL_C_INCLUDES += $(wildcard $(LOCAL_PATH)/../deps/)
	FILE_LIST += $(wildcard $(LOCAL_PATH)/../deps/*/*.cpp)
	FILE_LIST += $(wildcard $(LOCAL_PATH)/../deps/*/*.c)
	LOCAL_C_INCLUDES += $(wildcard $(LOCAL_PATH)/../src/)
	FILE_LIST += $(wildcard $(LOCAL_PATH)/../src/*.cpp)
	FILE_LIST += $(wildcard $(LOCAL_PATH)/../src/*.c)

	LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

	LOCAL_CFLAGS += -w
	LOCAL_CFLAGS += -s
	LOCAL_CFLAGS += -fvisibility=default
	LOCAL_CFLAGS += -fpack-struct=1
	LOCAL_CFLAGS += -fexceptions
	LOCAL_CFLAGS += -pthread
	LOCAL_CFLAGS += -Wall
	LOCAL_CFLAGS += -O2
	LOCAL_CFLAGS += -DNDEBUG
	LOCAL_CFLAGS += -DHOST_ENDIAN_IS_LITTLE
	LOCAL_CFLAGS += -DLITTLE_ENDIAN
	LOCAL_CFLAGS += -D_ARM_
	LOCAL_CFLAGS += -std=c11
	LOCAL_CPPFLAGS += -std=c++14

	include $(BUILD_SHARED_LIBRARY)
endif

