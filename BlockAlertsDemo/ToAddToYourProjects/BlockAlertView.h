//
//  BlockAlertView.h
//
//

#import <UIKit/UIKit.h>

@interface BlockAlertView : NSObject {
@protected
    UIView *_view;
    NSMutableArray *_blocks;
    CGFloat _height;
    NSString *_title;
    NSString *_message;
    BOOL _shown;
    BOOL _cancelBounce;
}

@property (nonatomic, strong) UIImage *backgroundImage;
@property (nonatomic, readonly) UIView *view;
@property (nonatomic, readwrite) BOOL vignetteBackground;

//Converting to ARC, [self retain] and [self autorelease] used in showInView: and dismissWithClickedButtonIndex:animated: were removed. Though the design is questionable in the first place. This property is a replacement for the old technique.
@property (nonatomic, strong) BlockAlertView* selfReference;

+ (BlockAlertView *)alertWithTitle:(NSString *)title message:(NSString *)message;

+ (void)showInfoAlertWithTitle:(NSString *)title message:(NSString *)message;
+ (void)showErrorAlert:(NSError *)error;

- (id)initWithTitle:(NSString *)title message:(NSString *)message;

- (void)addButtonWithTitle:(NSString *)title
               normalImage:(NSString*)normalImage
                     block:(void (^)())block;

- (void)addButtonWithTitle:(NSString *)title
               normalImage:(NSString*)normalImage
             selectedImage:(NSString*) selectedImage
             disabledImage:(NSString*) disabledImage
                     block:(void (^)())block;

- (void)addComponents:(CGRect)frame;

- (void)show;
- (void)dismissWithClickedButtonIndex:(NSInteger)buttonIndex animated:(BOOL)animated;

- (void)setupDisplay;


@end
