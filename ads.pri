
CONFIG(debug, debug|release){
    win32-g++ {
    	versionAtLeast(QT_VERSION, 5.15.0) {
    		LIBS += -lcsadvanceddocking
    	}
    	else {
    		LIBS += -lcsadvanceddockingd
    	}
    }
    else:msvc {
        LIBS += -lcsadvanceddockingd
    }
    else:mac {
        LIBS += -lcsadvanceddocking_debug
    }
    else {
        LIBS += -lcsadvanceddocking
    }
}
else{
    LIBS += -lcsadvanceddocking
}


unix:!macx {
    LIBS += -lxcb
}
