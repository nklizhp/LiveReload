
#import "CompileFileActionRow.h"
#import "ATMacViewCreation.h"
#import "ATAutolayout.h"
#import "CompileFileAction.h"


@implementation CompileFileActionRow

- (void)loadContent {
    [super loadContent];

    self.sourcePopUp = [[[[NSPopUpButton popUpButton] withBezelStyle:NSRoundRectBezelStyle] withTarget:self action:@selector(sourceOptionSelected:)] addedToView:self];
    self.destinationPopUp = [[[[NSPopUpButton popUpButton] withBezelStyle:NSRoundRectBezelStyle] withTarget:self action:@selector(destinationOptionSelected:)] addedToView:self];

    [self addConstraintsWithVisualFormat:@"|-indentL2-[checkbox(>=200)]-[sourcePopUp(>=120)]-columnGapMin-[destinationPopUp(>=120)]-(>=buttonBarGapMin)-[optionsButton]-buttonGap-[removeButton]|" options:NSLayoutFormatAlignAllCenterY];
    [self addFullHeightConstraintsForSubview:self.sourcePopUp];

    //    [self alignView:self.checkbox toColumnNamed:@"actionRightEdge" alignment:ATStackViewColumnAlignmentTrailing];
    [self alignView:self.sourcePopUp toColumnNamed:@"from"];
    [self alignView:self.destinationPopUp toColumnNamed:@"to"];

    [self.checkbox bind:@"value" toObject:self.representedObject withKeyPath:@"enabled" options:nil];
}

- (void)updateContent {
    [super updateContent];
    self.checkbox.title = self.action.label;
}

- (void)updateFilterOptions {
    CompileFileAction *xaction = (CompileFileAction *)self.action;
    [self updateFilterOptionsPopUp:self.sourcePopUp selectedOption:self.action.inputFilterOption];
    [self updateFilterOptionsPopUp:self.destinationPopUp selectedOption:xaction.outputFilterOption];
}

- (IBAction)sourceOptionSelected:(NSPopUpButton *)sender {
    CompileFileAction *xaction = (CompileFileAction *)self.action;
    FilterOption *filterOption = sender.selectedItem.representedObject;

    BOOL same = ([xaction.inputFilterOption.subfolder isEqualToString:xaction.outputFilterOption.subfolder]);
    xaction.inputFilterOption = filterOption;
    if (same) {
        xaction.outputFilterOption = filterOption;
    }
}

- (IBAction)destinationOptionSelected:(NSPopUpButton *)sender {
    CompileFileAction *xaction = (CompileFileAction *)self.action;
    FilterOption *filterOption = sender.selectedItem.representedObject;
    xaction.outputFilterOption = filterOption;
}

+ (NSArray *)representedObjectKeyPathsToObserve {
    return @[@"inputFilterOption", @"outputFilterOption"];
}

- (void)loadOptionsIntoView:(LROptionsView *)container {
    for (LROption *option in [self.action createOptions]) {
        [container addOption:option];
    }
}

@end
