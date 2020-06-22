//
//  DBoW2Wrapper.h
//  ArNavigation
//
//  Created by Vilen Looga on 23/01/2019.
//  Copyright © 2019 vimai. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface DBoW2Wrapper : NSObject

//-(bool) createDatabase: (NSArray *) images;

-(NSDictionary *) query: (NSString *) pathToImage;

-(bool) saveDBOWModel: (NSString *) filePath;
-(bool) loadDBOWModel: (NSString *) filePath;
-(void) clearDBOWModel;
@end

NS_ASSUME_NONNULL_END
