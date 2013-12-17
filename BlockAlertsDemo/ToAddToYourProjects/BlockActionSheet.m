//
//  BlockActionSheet.m
//
//

#import "BlockActionSheet.h"
#import "BlockBackground.h"
#import "BlockUI.h"

@implementation BlockActionSheet

@synthesize view = _view;
@synthesize vignetteBackground = _vignetteBackground;

static UIImage *background = nil;
static UIFont *titleFont = nil;
static UIFont *buttonFont = nil;

#pragma mark - init

+ (void)initialize
{
    if (self == [BlockActionSheet class])
    {
        background = [UIImage imageNamed:kActionSheetBackground];
        background = [background stretchableImageWithLeftCapWidth:0 topCapHeight:kActionSheetBackgroundCapHeight];

        titleFont = (kActionSheetButtonUsesSystemFont) ?
        ((kActionSheetButtonSystemFontIsBold) ?
         [UIFont boldSystemFontOfSize:kActionSheetButtonSystemFontSize] :
         [UIFont systemFontOfSize:kActionSheetButtonSystemFontSize]) :
        [UIFont fontWithName:kActionSheetButtonFontNameIfNotSystem size:kActionSheetButtonFontSizeIfNotSystem];

        buttonFont = (kActionSheetButtonUsesSystemFont) ?
        ((kActionSheetButtonSystemFontIsBold) ?
         [UIFont boldSystemFontOfSize:kActionSheetButtonSystemFontSize] :
         [UIFont systemFontOfSize:kActionSheetButtonSystemFontSize]) :
        [UIFont fontWithName:kActionSheetButtonFontNameIfNotSystem size:kActionSheetButtonFontSizeIfNotSystem];
    }
}

+ (id)sheetWithTitle:(NSString *)title
{
    return [[BlockActionSheet alloc] initWithTitle:title];
}

- (id)initWithTitle:(NSString *)title
{
    if ((self = [super init]))
    {
        UIWindow *parentView = [BlockBackground sharedInstance];
        CGRect frame = parentView.bounds;

        _view = [[UIView alloc] initWithFrame:frame];

        _view.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleTopMargin;

        _blocks = [[NSMutableArray alloc] init];
        _height = kActionSheetTopMargin;

        if (title)
        {
            CGSize size = [title sizeWithFont:titleFont
                            constrainedToSize:CGSizeMake(frame.size.width-kActionSheetBorder*2, 1000)
                                lineBreakMode:NSLineBreakByWordWrapping];

            UILabel *labelView = [[UILabel alloc] initWithFrame:CGRectMake(kActionSheetBorder, _height, frame.size.width-kActionSheetBorder*2, size.height)];
            labelView.font = titleFont;
            labelView.numberOfLines = 0;
            labelView.lineBreakMode = NSLineBreakByWordWrapping;
            labelView.textColor = kActionSheetTitleTextColor;
            labelView.backgroundColor = [UIColor clearColor];
            labelView.textAlignment = NSTextAlignmentCenter;
            labelView.shadowColor = kActionSheetTitleShadowColor;
            labelView.shadowOffset = kActionSheetTitleShadowOffset;
            labelView.text = title;

            labelView.autoresizingMask = UIViewAutoresizingFlexibleWidth;

            [_view addSubview:labelView];

            _height += size.height + 5;
        }
        _vignetteBackground = NO;
    }

    return self;
}


- (NSUInteger)buttonCount
{
    return _blocks.count;
}

- (void)addButtonWithTitle:(NSString *)title
               normalImage:(NSString*)normalImage
                     block:(void (^)())block
{
    [_blocks addObject:@[block ? [block copy] : [NSNull null],
                         title,
                         normalImage, [NSNull null], [NSNull null]]];
}

- (void)addButtonWithTitle:(NSString *)title
               normalImage:(NSString*)normalImage
             selectedImage:(NSString*) selectedImage
             disabledImage:(NSString*) disabledImage
                     block:(void (^)())block
{
    [_blocks addObject:@[block ? [block copy] : [NSNull null],
                         title,
                         normalImage, selectedImage, disabledImage]];
}


- (void)showInView:(UIView *)view
{
    NSUInteger i = 1;
    for (NSArray *block in _blocks)
    {
        NSString *title = [block objectAtIndex:1];
        NSString *normalImageName = [block objectAtIndex:2];
        NSString *selectedImageName = [block objectAtIndex:3];
        NSString *disabledImageName = [block objectAtIndex:4];

        UIImage *image = [UIImage imageNamed:normalImageName];
        image = [image stretchableImageWithLeftCapWidth:(int)(image.size.width+1)>>1 topCapHeight:0];

        UIImage *highlightedImage = nil;
        if ((NSNull*)selectedImageName != [NSNull null])
        {
            highlightedImage = [UIImage imageNamed:selectedImageName];
            highlightedImage = [highlightedImage stretchableImageWithLeftCapWidth:(int)(highlightedImage.size.width+1)>>1 topCapHeight:0];
        }
        UIImage *disabledImage = nil;
        if ((NSNull*)disabledImageName != [NSNull null])
        {
            disabledImage = [UIImage imageNamed:disabledImageName];
            disabledImage = [disabledImage stretchableImageWithLeftCapWidth:(int)(disabledImage.size.width+1)>>1 topCapHeight:0];
        }

        UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
        button.frame = CGRectMake(kActionSheetBorder, _height, _view.bounds.size.width-kActionSheetBorder*2, kActionSheetButtonHeight);
        button.titleLabel.font = buttonFont;
        if (IOS_LESS_THAN_6) {
#pragma clan diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
            button.titleLabel.minimumFontSize = 10;
#pragma clan diagnostic pop
        }
        else {
            button.titleLabel.minimumScaleFactor = 0.1;
        }
        button.titleLabel.adjustsFontSizeToFitWidth = YES;
        button.titleLabel.textAlignment = NSTextAlignmentCenter;
        button.titleLabel.shadowOffset = kActionSheetButtonShadowOffset;
        button.backgroundColor = [UIColor clearColor];
        button.tag = i++;

        [button setBackgroundImage:image forState:UIControlStateNormal];
        button.tintColor = [UIColor colorWithRed:0.5 green:0.5 blue:0.5 alpha:1.0];
        if (highlightedImage)
        {
            [button setBackgroundImage:highlightedImage forState:UIControlStateHighlighted];
        }
        if (disabledImage)
        {
            [button setBackgroundImage:disabledImage forState:UIControlStateDisabled];
            [button setTitleColor:[UIColor colorWithRed:0.5 green:0.5 blue:0.5 alpha:1.0] forState:UIControlStateDisabled];
        }

        [button setTitleColor:kActionSheetButtonTextColor forState:UIControlStateNormal];
        [button setTitleShadowColor:kActionSheetButtonShadowColor forState:UIControlStateNormal];
        [button setTitle:title forState:UIControlStateNormal];
        button.accessibilityLabel = title;

        [button addTarget:self action:@selector(buttonClicked:) forControlEvents:UIControlEventTouchUpInside];

        button.autoresizingMask = UIViewAutoresizingFlexibleWidth;

        [_view addSubview:button];
        _height += kActionSheetButtonHeight + kActionSheetBorder;
    }

    UIImageView *modalBackground = [[UIImageView alloc] initWithFrame:_view.bounds];
    modalBackground.image = background;
    modalBackground.contentMode = UIViewContentModeScaleToFill;
    modalBackground.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    [_view insertSubview:modalBackground atIndex:0];

    [BlockBackground sharedInstance].vignetteBackground = _vignetteBackground;
    [[BlockBackground sharedInstance] addToMainWindow:_view];
    CGRect frame = _view.frame;
    frame.origin.y = [BlockBackground sharedInstance].bounds.size.height;
    frame.size.height = _height + kActionSheetBounce;
    _view.frame = frame;

    __block CGPoint center = _view.center;
    center.y -= _height + kActionSheetBounce;

    [UIView animateWithDuration:0.4
                          delay:0.0
                        options:UIViewAnimationOptionCurveEaseOut
                     animations:^{
                         [BlockBackground sharedInstance].alpha = 1.0f;
                         _view.center = center;
                     } completion:^(BOOL finished) {
                         [UIView animateWithDuration:0.1
                                               delay:0.0
                                             options:UIViewAnimationOptionAllowUserInteraction
                                          animations:^{
                                              center.y += kActionSheetBounce;
                                              _view.center = center;
                                          } completion:nil];
                     }];
    self.selfReference = self; //Intentional retain cycle to keep
    //self maintained object alive.
}

- (void)dismissWithClickedButtonIndex:(NSInteger)buttonIndex animated:(BOOL)animated
{
    if (buttonIndex >= 0 && buttonIndex < [_blocks count])
    {
        id obj = [[_blocks objectAtIndex: buttonIndex] objectAtIndex:0];
        if (![obj isEqual:[NSNull null]])
        {
            ((void (^)())obj)();
        }
    }

    if (animated)
    {
        CGPoint center = _view.center;
        center.y += _view.bounds.size.height;
        [UIView animateWithDuration:0.4
                              delay:0.0
                            options:UIViewAnimationOptionCurveEaseIn
                         animations:^{
                             _view.center = center;
                             [[BlockBackground sharedInstance] reduceAlphaIfEmpty];
                         } completion:^(BOOL finished) {
                             [[BlockBackground sharedInstance] removeView:_view];
                             _view = nil;
                             self.selfReference = nil;
                         }];
    }
    else
    {
        [[BlockBackground sharedInstance] removeView:_view];
        _view = nil;
        self.selfReference = nil;
    }
}

#pragma mark - Action

- (void)buttonClicked:(id)sender
{
    /* Run the button's block */
    int buttonIndex = [(UIButton *)sender tag] - 1;
    [self dismissWithClickedButtonIndex:buttonIndex animated:YES];
}

@end
