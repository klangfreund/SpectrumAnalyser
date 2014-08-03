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

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.1.0" -D "JUCE_APP_VERSION_HEX=0x100" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../SpectrumAnalyser/JuceLibraryCode/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.1.0" -D "JUCE_APP_VERSION_HEX=0x100" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../SpectrumAnalyser/JuceLibraryCode/modules
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

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.1.0" -D "JUCE_APP_VERSION_HEX=0x100" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../SpectrumAnalyser/JuceLibraryCode/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -fvisibility=hidden -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.1.0" -D "JUCE_APP_VERSION_HEX=0x100" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../SpectrumAnalyser/JuceLibraryCode/modules
  TARGET := HiReSamStandalone
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/SamWithBubble_81c52742.o \
  $(OBJDIR)/SpectrumAnalyserAudioProcessor_b5547c25.o \
  $(OBJDIR)/SpectrumAnalyserAudioProcessorEditor_d7632732.o \
  $(OBJDIR)/SpectrumProcessor_18cdeed2.o \
  $(OBJDIR)/SpectrumViewer_d2a7371c.o \
  $(OBJDIR)/Main_90ebc5c2.o \
  $(OBJDIR)/BinaryData_ce4232d4.o \
  $(OBJDIR)/dRowAudio_dc8b664b.o \
  $(OBJDIR)/juce_audio_basics_e0b7b8ba.o \
  $(OBJDIR)/juce_audio_devices_1757c6f8.o \
  $(OBJDIR)/juce_audio_formats_45d91098.o \
  $(OBJDIR)/juce_audio_processors_2c2d3872.o \
  $(OBJDIR)/juce_audio_utils_e2729ab8.o \
  $(OBJDIR)/juce_core_bfacf59c.o \
  $(OBJDIR)/juce_data_structures_11318c58.o \
  $(OBJDIR)/juce_events_ac533410.o \
  $(OBJDIR)/juce_graphics_f81f8b74.o \
  $(OBJDIR)/juce_gui_basics_7b4818f0.o \
  $(OBJDIR)/juce_gui_extra_91bbc678.o \

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

$(OBJDIR)/SamWithBubble_81c52742.o: ../../../SpectrumAnalyser/Source/SamWithBubble.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SamWithBubble.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SpectrumAnalyserAudioProcessor_b5547c25.o: ../../../SpectrumAnalyser/Source/SpectrumAnalyserAudioProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SpectrumAnalyserAudioProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SpectrumAnalyserAudioProcessorEditor_d7632732.o: ../../../SpectrumAnalyser/Source/SpectrumAnalyserAudioProcessorEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SpectrumAnalyserAudioProcessorEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SpectrumProcessor_18cdeed2.o: ../../../SpectrumAnalyser/Source/SpectrumProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SpectrumProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SpectrumViewer_d2a7371c.o: ../../../SpectrumAnalyser/Source/SpectrumViewer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SpectrumViewer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Main_90ebc5c2.o: ../../Source/Main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Main.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/dRowAudio_dc8b664b.o: ../../../SpectrumAnalyser/JuceLibraryCode/modules/dRowAudio/dRowAudio/dRowAudio.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling dRowAudio.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_e0b7b8ba.o: ../../../SpectrumAnalyser/JuceLibraryCode/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_devices_1757c6f8.o: ../../../SpectrumAnalyser/JuceLibraryCode/modules/juce_audio_devices/juce_audio_devices.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_45d91098.o: ../../../SpectrumAnalyser/JuceLibraryCode/modules/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_processors_2c2d3872.o: ../../../SpectrumAnalyser/JuceLibraryCode/modules/juce_audio_processors/juce_audio_processors.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_utils_e2729ab8.o: ../../../SpectrumAnalyser/JuceLibraryCode/modules/juce_audio_utils/juce_audio_utils.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_utils.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_bfacf59c.o: ../../../SpectrumAnalyser/JuceLibraryCode/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_11318c58.o: ../../../SpectrumAnalyser/JuceLibraryCode/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_ac533410.o: ../../../SpectrumAnalyser/JuceLibraryCode/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_f81f8b74.o: ../../../SpectrumAnalyser/JuceLibraryCode/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_7b4818f0.o: ../../../SpectrumAnalyser/JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_91bbc678.o: ../../../SpectrumAnalyser/JuceLibraryCode/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
