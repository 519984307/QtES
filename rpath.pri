unix:!macx{
    QMAKE_LFLAGS += -Wl,-rpath=\'\$\$ORIGIN\'
    QMAKE_LFLAGS += -Wl,-rpath=$$LIB_DIR
    CONFIG(debug, release|debug){
        QMAKE_LFLAGS += -Wl,-rpath-link=$$LIB_DIR
    } else{
        QMAKE_LFLAGS += -Wl,-rpath-link=$$LIB_DIR
    }
}
