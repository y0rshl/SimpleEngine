//
//  AppDelegate.m
//  osx
//
//  Created by SANDSTORM04 on 7/23/16.
//  Copyright (c) 2016 ITBA. All rights reserved.
//

#import "AppDelegate.h"
#import <core>

@interface AppDelegate ()

@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
    Mesh::Load();
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
    return YES;
}

@end
