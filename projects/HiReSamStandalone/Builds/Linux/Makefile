# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.1.0" -D "JUCE_APP_VERSION_HEX=0x100" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../HiReSam/JuceLibraryCode/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.1.0" -D "JUCE_APP_VERSION_HEX=0x100" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../HiReSam/JuceLibraryCode/modules
  TARGET := HiReSamStandalone
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.1.0" -D "JUCE_APP_VERSION_HEX=0x100" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../HiReSam/JuceLibraryCode/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -fvisibility=hidden -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.1.0" -D "JUCE_APP_VERSION_HEX=0x100" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../HiReSam/JuceLibraryCode/modules
  TARGET := HiReSamStandalone
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/HiReSamAudioProcessor_eed54ffb.o \
  $(OBJDIR)/HiReSamAudioProcessorEditor_ec2f4288.o \
  $(OBJDIR)/PitchDetectorComponent_666b212d.o \
  $(OBJDIR)/SamWithBubble_b793d5c5.o \
  $(OBJDIR)/Spectroscope_f2ebca74.o \
  $(OBJDIR)/Main_90ebc5c2.o \
  $(OBJDIR)/BinaryData_ce4232d4.o \
  $(OBJDIR)/dRowAudio_f70bd428.o \
  $(OBJDIR)/juce_audio_basics_cd338cd7.o \
  $(OBJDIR)/juce_audio_devices_d42f07d5.o \
  $(OBJDIR)/juce_audio_formats_2b05175.o \
  $(OBJDIR)/juce_audio_processors_e5559f8f.o \
  $(OBJDIR)/juce_audio_utils_c91ed215.o \
  $(OBJDIR)/juce_core_e606a3b9.o \
  $(OBJDIR)/juce_data_structures_1c9316b5.o \
  $(OBJDIR)/juce_events_93be8bad.o \
  $(OBJDIR)/juce_graphics_4abcc91.o \
  $(OBJDIR)/juce_gui_basics_f764838d.o \
  $(OBJDIR)/juce_gui_extra_ac3c3455.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking HiReSamStandalone
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning HiReSamStandalone
	@$(CLEANCMD)

strip:
	@echo Stripping HiReSamStandalone
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/HiReSamAudioProcessor_eed54ffb.o: ../../../HiReSam/Source/HiReSamAudioProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling HiReSamAudioProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/HiReSamAudioProcessorEditor_ec2f4288.o: ../../../HiReSam/Source/HiReSamAudioProcessorEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling HiReSamAudioProcessorEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PitchDetectorComponent_666b212d.o: ../../../HiReSam/Source/PitchDetectorComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PitchDetectorComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SamWithBubble_b793d5c5.o: ../../../HiReSam/Source/SamWithBubble.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SamWithBubble.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Spectroscope_f2ebca74.o: ../../../HiReSam/Source/Spectroscope.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Spectroscope.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Main_90ebc5c2.o: ../../Source/Main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Main.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/dRowAudio_f70bd428.o: ../../../HiReSam/JuceLibraryCode/modules/dRowAudio/dRowAudio/dRowAudio.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling dRowAudio.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_cd338cd7.o: ../../../HiReSam/JuceLibraryCode/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_devices_d42f07d5.o: ../../../HiReSam/JuceLibraryCode/modules/juce_audio_devices/juce_audio_devices.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_2b05175.o: ../../../HiReSam/JuceLibraryCode/modules/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_processors_e5559f8f.o: ../../../HiReSam/JuceLibraryCode/modules/juce_audio_processors/juce_audio_processors.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_utils_c91ed215.o: ../../../HiReSam/JuceLibraryCode/modules/juce_audio_utils/juce_audio_utils.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_utils.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_e606a3b9.o: ../../../HiReSam/JuceLibraryCode/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_1c9316b5.o: ../../../HiReSam/JuceLibraryCode/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_93be8bad.o: ../../../HiReSam/JuceLibraryCode/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_4abcc91.o: ../../../HiReSam/JuceLibraryCode/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_f764838d.o: ../../../HiReSam/JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_ac3c3455.o: ../../../HiReSam/JuceLibraryCode/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
