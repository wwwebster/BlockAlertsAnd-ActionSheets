//
//  BlockActionSheet.h
//
//

#import <UIKit/UIKit.h>

/**
 * A simple block-enabled API wrapper on top of UIActionSheet.
 */
@interface BlockActionSheet : NSObject {
@private
    UIView *_view;
    NSMutableArray *_blocks;
    CGFloat _height;
}

@property (nonatomic, readonly) UIView *view;
@property (nonatomic, readwrite) BOOL vignetteBackground;

//Converting to ARC, [self retain] and [self autorelease] used in showInView: and dismissWithClickedButtonIndex:animated: were removed. Though the design is questionable in the first place, this property is a replacement for the old technique.
@property (nonatomic, strong) BlockActionSheet* selfReference;

+ (id)sheetWithTitle:(NSString *)title;
- (id)initWithTitle:(NSString *)title;

- (void)addButtonWithTitle:(NSString *)title
               normalImage:(NSString*)normalImage
                     block:(void (^)())block;

- (void)addButtonWithTitle:(NSString *)title
               normalImage:(NSString*)normalImage
             selectedImage:(NSString*) selectedImage
             disabledImage:(NSString*) disabledImage
                     block:(void (^)())block;

- (void)showInView:(UIView *)view;

- (NSUInteger)buttonCount;

@end
