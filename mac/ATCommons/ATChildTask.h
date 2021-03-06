
#import <Foundation/Foundation.h>


////////////////////////////////////////////////////////////////////////////////

typedef enum {
    ATLaunchUnixTaskAndCaptureOutputOptionsNone = 0,
    ATLaunchUnixTaskAndCaptureOutputOptionsMergeStdoutAndStderr = 0x01,
    ATLaunchUnixTaskAndCaptureOutputOptionsIgnoreSandbox = 0x02,
} ATLaunchUnixTaskAndCaptureOutputOptions;

typedef void (^ATLaunchUnixTaskAndCaptureOutputCompletionHandler)(NSString *outputText, NSString *stderrText, NSError *error);

extern NSString *ATCurrentDirectoryPathKey;

id ATLaunchUnixTaskAndCaptureOutput(NSURL *scriptURL, NSArray *arguments, ATLaunchUnixTaskAndCaptureOutputOptions flags, NSDictionary *options, ATLaunchUnixTaskAndCaptureOutputCompletionHandler handler);


////////////////////////////////////////////////////////////////////////////////
#pragma mark -


// returns NSUserUnixTask or PlainUnixTask or nil, depending on whether sandboxing is enabled
id ATCreateUserUnixTask(NSURL *scriptURL, NSError **error);


// API-compatible with NSUserUnixTask
@interface ATPlainUnixTask : NSObject

- (id)initWithURL:(NSURL *)url error:(NSError **)error;

@property(strong, readonly) NSURL *url;

// Standard I/O streams.  Setting them to nil (the default) will bind them to /dev/null.
// NSFileHandle or NSPipe
@property(strong) id standardInput;
@property(strong) id standardOutput;
@property(strong) id standardError;

@property(strong) NSString *currentDirectoryPath;

// Execute the file with the given arguments.  "arguments" is an array of NSStrings.  The arguments do not undergo shell expansion, so you do not need to do special quoting, and shell variables are not resolved.
typedef void (^PlainUnixTaskCompletionHandler)(NSError *error);
- (void)executeWithArguments:(NSArray *)arguments completionHandler:(PlainUnixTaskCompletionHandler)handler;

@end


extern NSString *ATPlainUnixTaskErrorDomain;
enum {
    PlainUnixTaskErrNonZeroExit = 1,
    PlainUnixTaskErrSandboxedTasksNotSupportedBefore10_8
};


////////////////////////////////////////////////////////////////////////////////
#pragma mark -

@interface ATTaskOutputReader : NSObject

- (id)init;
- (id)initWithTask:(id)task;

@property(strong, readonly) NSPipe *standardOutputPipe;
@property(strong, readonly) NSPipe *standardErrorPipe;

@property(strong, readonly) NSData *standardOutputData;
@property(strong, readonly) NSData *standardErrorData;

@property(strong, readonly) NSString *standardOutputText;
@property(strong, readonly) NSString *standardErrorText;
@property(strong, readonly) NSString *combinedOutputText;

- (void)launched;
- (void)startReading;

- (void)waitForCompletion:(void(^)())completionBlock;

@end
