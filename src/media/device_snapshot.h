// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2017 Intel Corporation. All Rights Reserved.

#pragma once

#include <map>
#include <memory>
#include "../core/extension.h"

namespace librealsense
{
    class snapshot_collection
    {
    public:
        snapshot_collection() {}
        snapshot_collection(const std::map<rs2_extension, std::shared_ptr<extension_snapshot>>& snapshots) :
            m_snapshots(snapshots)
        {
        }

        std::shared_ptr<extension_snapshot> find(rs2_extension t)
        {
            auto snapshot_it = m_snapshots.find(t);
            if(snapshot_it == std::end(m_snapshots))
            {
                return nullptr;
            }
            return snapshot_it->second;
        }
        std::map<rs2_extension, std::shared_ptr<extension_snapshot>> get_snapshots() const
        {
            return m_snapshots;
        }

        const std::shared_ptr<extension_snapshot>& operator[](rs2_extension extension) const
        {
            return m_snapshots.at(extension);
        }

        std::shared_ptr<extension_snapshot>& operator[](rs2_extension extension)
        {
            return m_snapshots[extension];
        }
    private:
        std::map<rs2_extension, std::shared_ptr<extension_snapshot>> m_snapshots;
    };

    class sensor_snapshot
    {
    public:
        sensor_snapshot(const snapshot_collection& sensor_extensions) : m_snapshots(sensor_extensions) {}
        sensor_snapshot(const snapshot_collection& sensor_extensions, stream_profiles streams) :
            m_snapshots(sensor_extensions),
            m_streams(streams)
        {
        }
        snapshot_collection get_sensor_extensions_snapshots() const
        {
            return m_snapshots;
        }
        stream_profiles get_stream_profiles() const
        {
            return m_streams;
        }
    private:
        snapshot_collection m_snapshots;
        stream_profiles m_streams;
    };
    using device_extrinsics = std::map<std::tuple<size_t, rs2_stream, size_t, rs2_stream>, rs2_extrinsics>;

    class device_snapshot
    {
    public:
        device_snapshot() {}
        device_snapshot(const snapshot_collection& device_extensios, const std::vector<sensor_snapshot>& sensors_snapshot) :
            m_device_snapshots(device_extensios),
            m_sensors_snapshot(sensors_snapshot)
        {

        }
        std::vector<sensor_snapshot> get_sensors_snapshots() const
        {
            return m_sensors_snapshot;
        }
        snapshot_collection get_device_extensions_snapshots() const
        {
            return m_device_snapshots;
        }
    private:
        snapshot_collection m_device_snapshots;
        std::vector<sensor_snapshot> m_sensors_snapshot;
    };
}
