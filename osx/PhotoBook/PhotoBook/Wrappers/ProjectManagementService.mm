//
//  ProjectManagementService.mm
//  PhotoBook
//
//  Created by Cosmin Mihai on 22.12.2024.
//
#import <Foundation/Foundation.h>

#include "ProjectManagementService.h"

@implementation ProjectManagementServiceWrapper

std::shared_ptr<PB::Service::ProjectManagementService> projectManagementServiceCpp = nullptr;

- (id) initWithCpp:(std::shared_ptr<PB::Service::ProjectManagementService>)projectManagementService
{
    projectManagementServiceCpp = projectManagementService;
    return self;
}

- (void) removeByName:(NSString*)name
{
    std::string nativeName = [name UTF8String];
    projectManagementServiceCpp->deleteProject(nativeName);
}

- (void)rename:(NSString*)oldName newName:(NSString*)newName
{
    std::string nativeOldName = [oldName UTF8String];
    std::string nativeNewName = [newName UTF8String];
    projectManagementServiceCpp->renameProject(nativeOldName, nativeNewName);
}

- (PaperSettings*) paperSettings
{
    auto project = projectManagementServiceCpp->maybeLoadedProjectInfo();
    auto nativePaperSettings = project->second.paperSettings;
    
    return [[PaperSettings alloc] initWithCpp: nativePaperSettings];
}

- (UnstagedImagesRepo*) unstagedImagesRepo
{
    auto maybeProject = projectManagementServiceCpp->maybeLoadedProjectInfo();
    
    return [[UnstagedImagesRepo alloc] initWithCpp:maybeProject->second.imageMonitor()];
}

- (StagedImagesView*) stagedImages
{
    auto maybeProject = projectManagementServiceCpp->maybeLoadedProjectInfo();
    
    return [[StagedImagesView alloc] initWithCpp:maybeProject->second.stagedImages()];
}

@end
