//
//  BlockUI.h
//
//  Created by Gustavo Ambrozio on 14/2/12.
//

#ifndef BlockUI_h
#define BlockUI_h

#if __IPHONE_OS_VERSION_MAX_ALLOWED < 60000
#define NSTextAlignmentCenter       UITextAlignmentCenter
#define NSLineBreakByWordWrapping   UILineBreakModeWordWrap
#define NSLineBreakByClipping       UILineBreakModeClip

#endif

#ifndef IOS_LESS_THAN_6
#define IOS_LESS_THAN_6 !([[[UIDevice currentDevice] systemVersion] compare:@"6.0" options:NSNumericSearch] != NSOrderedAscending)

#endif

#define NeedsLandscapePhoneTweaks (UIInterfaceOrientationIsLandscape([[UIApplication sharedApplication] statusBarOrientation]) && UI_USER_INTERFACE_IDIOM() != UIUserInterfaceIdiomPad)


#pragma mark - Configuration

static NSDictionary *alertViewConfigDictionary = nil;
static NSDictionary* getAlertViewConfigDictionary()
{
    if (alertViewConfigDictionary == nil)
    {
        NSString *configPath = [[NSBundle mainBundle] pathForResource:@"BlockUI" ofType:@"plist"];
        alertViewConfigDictionary = [[NSDictionary alloc] initWithContentsOfFile:configPath];
    }
    return alertViewConfigDictionary;
}

#define GetConfig(key) ((NSString*)getAlertViewConfigDictionary()[key])
#define GetConfigDict(key, subKey) ((NSString*)getAlertViewConfigDictionary()[key][subKey])


// Action Sheet constants

#define kActionSheetBounce                      GetConfig(@"kActionSheetBounce").floatValue
#define kActionSheetBorder                      GetConfig(@"kActionSheetBorder").floatValue
#define kActionSheetButtonHeight                GetConfig(@"kActionSheetButtonHeight").floatValue
#define kActionSheetTopMargin                   GetConfig(@"kActionSheetTopMargin").floatValue

#define kActionSheetTitleUsesSystemFont         GetConfig(@"kActionSheetTitleUsesSystemFont").boolValue
#define kActionSheetTitleSystemFontIsBold       GetConfig(@"kActionSheetTitleSystemFontIsBold").boolValue
#define kActionSheetTitleSystemFontSize         GetConfig(@"kActionSheetTitleSystemFontSize").floatValue
#define kActionSheetTitleFontNameIfNotSystem    GetConfig(@"kActionSheetTitleFontNameIfNotSystem")
#define kActionSheetTitleFontSizeIfNotSystem    GetConfig(@"kActionSheetTitleFontSizeIfNotSystem").floatValue
#define kActionSheetTitleTextColor              [UIColor colorWithRed:GetConfigDict(@"kActionSheetTitleTextColor", @"red").floatValue      \
green:GetConfigDict(@"kActionSheetTitleTextColor", @"green").floatValue    \
blue:GetConfigDict(@"kActionSheetTitleTextColor", @"blue").floatValue     \
alpha:GetConfigDict(@"kActionSheetTitleTextColor", @"alpha").floatValue]
#define kActionSheetTitleShadowColor            [UIColor colorWithRed:GetConfigDict(@"kActionSheetTitleShadowColor", @"red").floatValue     \
green:GetConfigDict(@"kActionSheetTitleShadowColor", @"green").floatValue   \
blue:GetConfigDict(@"kActionSheetTitleShadowColor", @"blue").floatValue    \
alpha:GetConfigDict(@"kActionSheetTitleShadowColor", @"alpha").floatValue ]
#define kActionSheetTitleShadowOffset           CGSizeMake(GetConfigDict(@"kActionSheetTitleShadowOffset", @"x").floatValue,    \
GetConfigDict(@"kActionSheetTitleShadowOffset", @"y").floatValue)

#define kActionSheetButtonUsesSystemFont        GetConfig(@"kActionSheetButtonUsesSystemFont").boolValue
#define kActionSheetButtonSystemFontIsBold      GetConfig(@"kActionSheetButtonSystemFontIsBold").boolValue
#define kActionSheetButtonSystemFontSize        GetConfig(@"kActionSheetButtonSystemFontSize").floatValue
#define kActionSheetButtonFontNameIfNotSystem   GetConfig(@"kActionSheetButtonFontNameIfNotSystem")
#define kActionSheetButtonFontSizeIfNotSystem   GetConfig(@"kActionSheetButtonFontSizeIfNotSystem").floatValue
#define kActionSheetButtonTextColor             [UIColor colorWithRed:GetConfigDict(@"kActionSheetButtonTextColor", @"red").floatValue      \
green:GetConfigDict(@"kActionSheetButtonTextColor", @"green").floatValue    \
blue:GetConfigDict(@"kActionSheetButtonTextColor", @"blue").floatValue     \
alpha:GetConfigDict(@"kActionSheetButtonTextColor", @"alpha").floatValue]
#define kActionSheetButtonShadowColor           [UIColor colorWithRed:GetConfigDict(@"kActionSheetButtonShadowColor", @"red").floatValue      \
green:GetConfigDict(@"kActionSheetButtonShadowColor", @"green").floatValue    \
blue:GetConfigDict(@"kActionSheetButtonShadowColor", @"blue").floatValue     \
alpha:GetConfigDict(@"kActionSheetButtonShadowColor", @"alpha").floatValue]
#define kActionSheetButtonShadowOffset          CGSizeMake(GetConfigDict(@"kActionSheetButtonShadowOffset", @"x").floatValue,    \
GetConfigDict(@"kActionSheetButtonShadowOffset", @"x").floatValue)

#define kActionSheetBackground                  GetConfig(@"kActionSheetBackground")
#define kActionSheetBackgroundCapHeight         GetConfig(@"kActionSheetBackgroundCapHeight").floatValue


// Alert View constants

#pragma mark - Alert View -
#pragma mark General

#define kAlertViewBounce         GetConfig(@"kAlertViewBounce").floatValue
#define kAlertViewBorder         (NeedsLandscapePhoneTweaks ? GetConfig(@"kAlertViewBorderLandscape").floatValue : \
GetConfig(@"kAlertViewBorderPortrait").floatValue)
#define kAlertButtonHeight       (NeedsLandscapePhoneTweaks ? GetConfig(@"kAlertButtonHeightLandscape").floatValue : \
GetConfig(@"kAlertButtonHeightPortrait").floatValue)

#pragma mark Title

#define kAlertViewTitleUsesSystemFont         GetConfig(@"kAlertViewTitleUsesSystemFont").boolValue
#define kAlertViewTitleSystemFontIsBold       GetConfig(@"kAlertViewTitleSystemFontIsBold").boolValue
#define kAlertViewTitleSystemFontSize         GetConfig(@"kAlertViewTitleSystemFontSize").floatValue
#define kAlertViewTitleFontNameIfNotSystem    GetConfig(@"kAlertViewTitleFontNameIfNotSystem")
#define kAlertViewTitleFontSizeIfNotSystem    GetConfig(@"kAlertViewTitleFontSizeIfNotSystem").floatValue
#define kAlertViewTitleTextColor              [UIColor colorWithRed:GetConfigDict(@"kAlertViewTitleTextColor", @"red").floatValue      \
green:GetConfigDict(@"kAlertViewTitleTextColor", @"green").floatValue    \
blue:GetConfigDict(@"kAlertViewTitleTextColor", @"blue").floatValue     \
alpha:GetConfigDict(@"kAlertViewTitleTextColor", @"alpha").floatValue]
#define kAlertViewTitleShadowColor            [UIColor colorWithRed:GetConfigDict(@"kAlertViewTitleShadowColor", @"red").floatValue     \
green:GetConfigDict(@"kAlertViewTitleShadowColor", @"green").floatValue   \
blue:GetConfigDict(@"kAlertViewTitleShadowColor", @"blue").floatValue    \
alpha:GetConfigDict(@"kAlertViewTitleShadowColor", @"alpha").floatValue ]
#define kAlertViewTitleShadowOffset           CGSizeMake(GetConfigDict(@"kAlertViewTitleShadowOffset", @"x").floatValue,    \
GetConfigDict(@"kAlertViewTitleShadowOffset", @"y").floatValue)

#pragma mark Message

#define kAlertViewMessageUsesSystemFont         GetConfig(@"kAlertViewMessageUsesSystemFont").boolValue
#define kAlertViewMessageSystemFontIsBold       GetConfig(@"kAlertViewMessageSystemFontIsBold").boolValue
#define kAlertViewMessageSystemFontSize         GetConfig(@"kAlertViewMessageSystemFontSize").floatValue
#define kAlertViewMessageFontNameIfNotSystem    GetConfig(@"kAlertViewMessageFontNameIfNotSystem")
#define kAlertViewMessageFontSizeIfNotSystem    GetConfig(@"kAlertViewMessageFontSizeIfNotSystem").floatValue
#define kAlertViewMessageTextColor              [UIColor colorWithRed:GetConfigDict(@"kAlertViewMessageTextColor", @"red").floatValue      \
green:GetConfigDict(@"kAlertViewMessageTextColor", @"green").floatValue    \
blue:GetConfigDict(@"kAlertViewMessageTextColor", @"blue").floatValue     \
alpha:GetConfigDict(@"kAlertViewMessageTextColor", @"alpha").floatValue]
#define kAlertViewMessageShadowColor            [UIColor colorWithRed:GetConfigDict(@"kAlertViewMessageShadowColor", @"red").floatValue     \
green:GetConfigDict(@"kAlertViewMessageShadowColor", @"green").floatValue   \
blue:GetConfigDict(@"kAlertViewMessageShadowColor", @"blue").floatValue    \
alpha:GetConfigDict(@"kAlertViewMessageShadowColor", @"alpha").floatValue ]
#define kAlertViewMessageShadowOffset           CGSizeMake(GetConfigDict(@"kAlertViewMessageShadowOffset", @"x").floatValue,    \
GetConfigDict(@"kAlertViewMessageShadowOffset", @"y").floatValue)

#pragma mark Button

#define kAlertViewButtonUsesSystemFont         GetConfig(@"kAlertViewButtonUsesSystemFont").boolValue
#define kAlertViewButtonSystemFontIsBold       GetConfig(@"kAlertViewButtonSystemFontIsBold").boolValue
#define kAlertViewButtonSystemFontSize         GetConfig(@"kAlertViewButtonSystemFontSize").floatValue
#define kAlertViewButtonFontNameIfNotSystem    GetConfig(@"kAlertViewButtonFontNameIfNotSystem")
#define kAlertViewButtonFontSizeIfNotSystem    GetConfig(@"kAlertViewButtonFontSizeIfNotSystem").floatValue
#define kAlertViewButtonTextColor              [UIColor colorWithRed:GetConfigDict(@"kAlertViewButtonTextColor", @"red").floatValue      \
green:GetConfigDict(@"kAlertViewButtonTextColor", @"green").floatValue    \
blue:GetConfigDict(@"kAlertViewButtonTextColor", @"blue").floatValue     \
alpha:GetConfigDict(@"kAlertViewButtonTextColor", @"alpha").floatValue]
#define kAlertViewButtonShadowColor            [UIColor colorWithRed:GetConfigDict(@"kAlertViewButtonShadowColor", @"red").floatValue     \
green:GetConfigDict(@"kAlertViewButtonShadowColor", @"green").floatValue   \
blue:GetConfigDict(@"kAlertViewButtonShadowColor", @"blue").floatValue    \
alpha:GetConfigDict(@"kAlertViewButtonShadowColor", @"alpha").floatValue ]
#define kAlertViewButtonShadowOffset           CGSizeMake(GetConfigDict(@"kAlertViewButtonShadowOffset", @"x").floatValue,    \
GetConfigDict(@"kAlertViewButtonShadowOffset", @"y").floatValue)

#pragma mark Backgrounds

#define kAlertViewBackgroundPortrait    GetConfig(@"kAlertViewBackgroundPortrait")
#define kAlertViewBackgroundLandscape   GetConfig(@"kAlertViewBackgroundLandscape")
#define kAlertViewBackgroundCapHeight   GetConfig(@"kAlertViewBackgroundCapHeight").floatValue

#endif
