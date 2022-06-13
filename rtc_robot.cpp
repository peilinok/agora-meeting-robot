#include "rtc_robot.h"

#include <iostream>
#include <thread>

#include "strtrans.h"

RtcRobot::RtcRobot(const std::wstring& appid, const std::wstring& rid,
                   const std::wstring& prefix, const std::wstring& source,
                   bool pub_audio, bool pub_video, const int& elapsed)
    : appid_(appid),
      rid_(rid),
      prefix_(prefix),
      source_(source),
      pub_audio_(pub_audio),
      pub_video_(pub_video),
      elapsed_(elapsed) {
  InitEngine();
}

RtcRobot::~RtcRobot() { ReleaseEngine(); }

void RtcRobot::Run() {
  JoinChannel();

  Sleep(elapsed_ * 1000);

  LeaveChannel();
}

void RtcRobot::InitEngine() {
  agora::rtc::RtcEngineContext context;

  std::string utf8_appid = strtrans::unicode_utf8(appid_);
  context.appId = utf8_appid.c_str();
  context.eventHandler = this;

  engine_ = createAgoraRtcEngine();
  int ret = engine_->initialize(context);
  std::wcout << L"initialize ret " << ret << std::endl;

  engine_->registerEventHandler(this);
  engine_->setChannelProfile(agora::CHANNEL_PROFILE_LIVE_BROADCASTING);

  agora::rtc::VideoEncoderConfiguration config;
  config.dimensions = agora::rtc::VideoDimensions(480, 360);
  // in 4.x version sdk, there has a min bitrate by resolution
  // if set two low here, will use a recommand bitrate
  config.bitrate = 800;
  config.frameRate = 10;
  engine_->setVideoEncoderConfiguration(config);

  // initialize media palyer
  player_ = engine_->createMediaPlayer();
  player_->registerPlayerSourceObserver(this);

  const std::string utf8_source = strtrans::unicode_utf8(source_);
  ret = player_->open(utf8_source.c_str(), 0);
  std::wcout << L"open source ret " << ret << std::endl;
}

void RtcRobot::ReleaseEngine() {
  if (engine_) {
    engine_->destroyMediaPlayer(player_);

    engine_->disableVideo();
    engine_->release(true);
  }
}

void RtcRobot::JoinChannel() {
  // join channel
  agora::rtc::ChannelMediaOptions options;
  options.clientRoleType = agora::rtc::CLIENT_ROLE_BROADCASTER;
  options.publishMediaPlayerVideoTrack = pub_video_;
  options.publishMediaPlayerAudioTrack = pub_audio_;
  options.publishMediaPlayerId = player_->getMediaPlayerId();
  options.publishAudioTrack = false;
  options.publishCameraTrack = false;
  options.autoSubscribeAudio = false;
  options.autoSubscribeVideo = false;

  std::string utf8_rid = strtrans::unicode_utf8(rid_);

  agora::rtc::uid_t uid = static_cast<agora::rtc::uid_t>(::GetTickCount());
  int ret = engine_->joinChannel("", utf8_rid.c_str(), uid, options);

  std::wcout << L"join channel with uid " << uid << L" ret " << ret
             << std::endl;
}

void RtcRobot::LeaveChannel() {
  player_->stop();
  engine_->leaveChannel();
}

// IRtcEngineEventHandlerEx
void RtcRobot::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid,
                                    int elapsed) {
  std::wcout << L"join channgel succeed" << std::endl;

  int ret = player_->play();
  std::wcout << L"play source ret " << ret << std::endl;

  engine_->enableMediaPlayerStreamMode(player_->getMediaPlayerId(), true);
  player_->setLoopCount(-1);
  player_->adjustPlayoutVolume(0);
}

void RtcRobot::onLeaveChannel(const agora::rtc::RtcStats& stats) {}

// IMediaPlayerSourceObserver

void RtcRobot::onPlayerSourceStateChanged(
    agora::media::base::MEDIA_PLAYER_STATE state,
    agora::media::base::MEDIA_PLAYER_ERROR ec) {}

void RtcRobot::onPositionChanged(int64_t position) {}

void RtcRobot::onPlayerEvent(agora::media::base::MEDIA_PLAYER_EVENT eventCode,
                             int64_t elapsedTime, const char* message) {}

void RtcRobot::onMetaData(const void* data, int length) {}

void RtcRobot::onPlayBufferUpdated(int64_t playCachedBuffer) {}

void RtcRobot::onPreloadEvent(const char* src,
                              agora::media::base::PLAYER_PRELOAD_EVENT event) {}

void RtcRobot::onCompleted() {}

void RtcRobot::onAgoraCDNTokenWillExpire() {}

void RtcRobot::onPlayerSrcInfoChanged(const agora::media::base::SrcInfo& from,
                                      const agora::media::base::SrcInfo& to) {}

void RtcRobot::onPlayerInfoUpdated(
    const agora::media::base::PlayerUpdatedInfo& info) {}

void RtcRobot::onAudioVolumeIndication(int volume) {}
