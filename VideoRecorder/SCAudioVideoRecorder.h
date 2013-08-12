//
//  VRVideoRecorder.h
//  VideoRecorder
//
//  Created by Simon CORSIN on 8/3/13.
//  Copyright (c) 2013 rFlex. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "SCVideoEncoder.h"
#import "SCAudioEncoder.h"

@class SCAudioVideoRecorder;

//
// VideoRecorderDelegate
//

@protocol SCAudioVideoRecorderDelegate <NSObject>

@optional

- (void) audioVideoRecorder:(SCAudioVideoRecorder *)audioVideoRecorder didRecordVideoFrame:(Float64)frameSecond;
- (void) audioVideoRecorder:(SCAudioVideoRecorder *)audioVideoRecorder didRecordAudioSample:(Float64)sampleSecond;
- (void) audioVideoRecorder:(SCAudioVideoRecorder *)audioVideoRecorder didFinishRecordingAtUrl:(NSURL*)recordedFile error:(NSError*)error;
- (void) audioVideoRecorder:(SCAudioVideoRecorder *)audioVideoRecorder didFailToInitializeVideoEncoder:(NSError*)error;
- (void) audioVideoRecorder:(SCAudioVideoRecorder *)audioVideoRecorder didFailToInitializeAudioEncoder:(NSError*)error;

@end

//
// AudioVideo Recorder
//

@class SCVideoEncoder;
@class SCAudioEncoder;

@interface SCAudioVideoRecorder : NSObject<SCDataEncoderDelegate> {
    
}

- (void) prepareRecordingAtCameraRoll:(NSError**)error;
- (NSURL*) prepareRecordingOnTempDir:(NSError**)error;
- (void) prepareRecordingAtUrl:(NSURL*)url error:(NSError**)error;

- (void) record;
- (void) pause;
- (void) cancel;
- (void) stop;

- (BOOL) isPrepared;
- (BOOL) isRecording;

@property (weak, nonatomic) id<SCAudioVideoRecorderDelegate> delegate;

@property (strong, nonatomic, readonly) AVCaptureVideoDataOutput * videoOutput;
@property (strong, nonatomic, readonly) AVCaptureAudioDataOutput * audioOutput;

// The VideoEncoder. Accessing this allow the configuration of the video encoder
@property (strong, nonatomic, readonly) SCVideoEncoder * videoEncoder;

// The AudioEncoder. Accessing this allow the configuration of the audio encoder
@property (strong, nonatomic, readonly) SCAudioEncoder * audioEncoder;

// When the recording is prepared, this getter contains the output file
@property (strong, nonatomic, readonly) NSURL * outputFileUrl;

// If true, every messages sent to the delegate will be dispatched through the main queue
@property (assign, nonatomic) BOOL dispatchDelegateMessagesOnMainQueue;

// Must be like AVFileType*
@property (copy, nonatomic) NSString * outputFileType;

@end
