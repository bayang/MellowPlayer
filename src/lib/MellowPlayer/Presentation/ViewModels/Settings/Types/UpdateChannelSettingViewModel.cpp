#include "UpdateChannelSettingViewModel.hpp"
#include <MellowPlayer/Domain/Settings/Setting.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;

UpdateChannelSettingViewModel::UpdateChannelSettingViewModel(Setting& setting, QObject* parent) : SettingViewModel(setting, parent)
{
}

QString UpdateChannelSettingViewModel::value() const
{
    UpdateChannel channel = static_cast<UpdateChannel>(setting_.value().toInt());
    return stringer_.toString(channel);
}

QStringList UpdateChannelSettingViewModel::values() const
{
    return QStringList() << stringer_.toString(UpdateChannel::Stable) << stringer_.toString(UpdateChannel::Beta)
                         << stringer_.toString(UpdateChannel::Continuous);
}

QString UpdateChannelSettingViewModel::qmlComponent()
{
    return "Delegates/EnumSettingDelegate.qml";
}

void UpdateChannelSettingViewModel::setValue(QString value)
{
    setting_.setValue(static_cast<int>(stringer_.fromString(value)));
}

void UpdateChannelSettingViewModel::onValueChanged()
{
    emit valueChanged();
}
