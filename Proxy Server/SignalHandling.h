//
//  SignalHandling.h
//  Proxy Server
//
//  Created by Matt Zanchelli on 2/20/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#ifndef Proxy_Server_SignalHandling_h
#define Proxy_Server_SignalHandling_h

#include <signal.h>

/// Handle a signal.
/// @param n The signal value to handle.
void handleSignal(int n);

/// Handle user-defined signal 1.
void handleSIGUSR1();

/// Handle user-defined signal 2.
void handleSIGUSR2();

#endif
