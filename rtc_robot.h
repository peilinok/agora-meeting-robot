#pragma once
#include <string>

#include "IAgoraMediaPlayer.h"
#include "IAgoraMediaPlayerSource.h"
#include "IAgoraRtcEngine.h"
#include "IAgoraRtcEngineEx.h"

class RtcRobot : public agora::rtc::IRtcEngineEventHandlerEx,
                 public agora::rtc::IMediaPlayerSourceObserver {
 public:
  RtcRobot(const std::wstring& appid, const std::wstring& rid,
           const std::wstring& prefix, const std::wstring& source,
           bool pub_audio, bool pub_video, const int& elapsed);
  ~RtcRobot();

  void Run();

 private:
  void InitEngine();
  void ReleaseEngine();
  void JoinChannel();
  void LeaveChannel();

 public:
  // IRtcEngineEventHandlerEx
  virtual void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid,
                                    int elapsed) override;
  virtual void onLeaveChannel(const agora::rtc::RtcStats& stats) override;

  // IMediaPlayerSourceObserver
  virtual void onPlayerSourceStateChanged(
      agora::media::base::MEDIA_PLAYER_STATE state,
      agora::media::base::MEDIA_PLAYER_ERROR ec) override;
  virtual void onPositionChanged(int64_t position) override;
  virtual void onPlayerEvent(agora::media::base::MEDIA_PLAYER_EVENT eventCode,
                             int64_t elapsedTime, const char* message) override;
  virtual void onMetaData(const void* data, int length) override;
  virtual void onPlayBufferUpdated(int64_t playCachedBuffer) override;
  virtual void onPreloadEvent(
      const char* src, agora::media::base::PLAYER_PRELOAD_EVENT event) override;
  virtual void onCompleted() override;
  virtual void onAgoraCDNTokenWillExpire() override;
  virtual void onPlayerSrcInfoChanged(
      const agora::media::base::SrcInfo& from,
      const agora::media::base::SrcInfo& to) override;
  virtual void onPlayerInfoUpdated(
      const agora::media::base::PlayerUpdatedInfo& info) override;
  virtual void onAudioVolumeIndication(int volume) override;

 private:
  std::wstring appid_;
  std::wstring rid_;
  std::wstring prefix_;
  std::wstring source_;
  int elapsed_;
  bool pub_audio_;
  bool pub_video_;

  agora::rtc::IRtcEngine* engine_ = nullptr;
  agora::agora_refptr<agora::rtc::IMediaPlayer> player_ = nullptr;
};