#pragma once
#ifndef MESSMER_CRYFS_FILESYSTEM_PARALLELACCESSFSBLOBSTORE_DIRBLOBREF_H
#define MESSMER_CRYFS_FILESYSTEM_PARALLELACCESSFSBLOBSTORE_DIRBLOBREF_H

#include "FsBlobRef.h"
#include "../cachingfsblobstore/DirBlobRef.h"
#include "../fsblobstore/utils/TimestampUpdateBehavior.h"
#include <fspp/fs_interface/Node.h>

namespace cryfs {
namespace parallelaccessfsblobstore {

class DirBlobRef final: public FsBlobRef {
public:
    DirBlobRef(cachingfsblobstore::DirBlobRef *base): _base(base) {}

    using Entry = fsblobstore::DirEntry;

    boost::optional<const Entry&> GetChild(const std::string &name) const {
        return _base->GetChild(name);
    }

    boost::optional<const Entry&> GetChild(const blockstore::BlockId &blockId) const {
        return _base->GetChild(blockId);
    }

    size_t NumChildren() const {
        return _base->NumChildren();
    }

    void RemoveChild(const blockstore::BlockId &blockId) {
        return _base->RemoveChild(blockId);
    }

    void RemoveChild(const std::string &name) {
        return _base->RemoveChild(name);
    }

    void flush() {
        return _base->flush();
    }

    void AddOrOverwriteChild(const std::string &name, const blockstore::BlockId &blobId, fspp::Dir::EntryType type,
                  fspp::mode_t mode, fspp::uid_t uid, fspp::gid_t gid, timespec lastAccessTime, timespec lastModificationTime,
                  std::function<void (const blockstore::BlockId &blockId)> onOverwritten) {
        return _base->AddOrOverwriteChild(name, blobId, type, mode, uid, gid, lastAccessTime, lastModificationTime, onOverwritten);
    }

    void RenameChild(const blockstore::BlockId &blockId, const std::string &newName, std::function<void (const blockstore::BlockId &blockId)> onOverwritten) {
        return _base->RenameChild(blockId, newName, onOverwritten);
    }

    fspp::Node::stat_info statChild(const blockstore::BlockId &blockId) const {
        return _base->statChild(blockId);
    }

    fspp::Node::stat_info statChildWithKnownSize(const blockstore::BlockId &blockId, uint64_t size) const {
        return _base->statChildWithKnownSize(blockId, size);
    }

    void updateAccessTimestampForChild(const blockstore::BlockId &blockId, fsblobstore::TimestampUpdateBehavior timestampUpdateBehavior) {
        return _base->updateAccessTimestampForChild(blockId, timestampUpdateBehavior);
    }

    void updateModificationTimestampForChild(const blockstore::BlockId &blockId) {
        return _base->updateModificationTimestampForChild(blockId);
    }

    void chmodChild(const blockstore::BlockId &blockId, fspp::mode_t mode) {
        return _base->chmodChild(blockId, mode);
    }

    void chownChild(const blockstore::BlockId &blockId, fspp::uid_t uid, fspp::gid_t gid) {
        return _base->chownChild(blockId, uid, gid);
    }

    void utimensChild(const blockstore::BlockId &blockId, timespec lastAccessTime, timespec lastModificationTime) {
        return _base->utimensChild(blockId, lastAccessTime, lastModificationTime);
    }

    void AddChildDir(const std::string &name, const blockstore::BlockId &blobId, fspp::mode_t mode, fspp::uid_t uid, fspp::gid_t gid, timespec lastAccessTime, timespec lastModificationTime) {
        return _base->AddChildDir(name, blobId, mode, uid, gid, lastAccessTime, lastModificationTime);
    }

    void AddChildFile(const std::string &name, const blockstore::BlockId &blobId, fspp::mode_t mode, fspp::uid_t uid, fspp::gid_t gid, timespec lastAccessTime, timespec lastModificationTime) {
        return _base->AddChildFile(name, blobId, mode, uid, gid, lastAccessTime, lastModificationTime);
    }

    void AddChildSymlink(const std::string &name, const blockstore::BlockId &blobId, fspp::uid_t uid, fspp::gid_t gid, timespec lastAccessTime, timespec lastModificationTime) {
        return _base->AddChildSymlink(name, blobId, uid, gid, lastAccessTime, lastModificationTime);
    }

    void AppendChildrenTo(std::vector<fspp::Dir::Entry> *result) const {
        return _base->AppendChildrenTo(result);
    }

    const blockstore::BlockId &blockId() const override {
        return _base->blockId();
    }

    off_t lstat_size() const override {
        return _base->lstat_size();
    }

    const blockstore::BlockId &parentPointer() const override {
        return _base->parentPointer();
    }

    void setParentPointer(const blockstore::BlockId &parentId) override {
        return _base->setParentPointer(parentId);
    }

private:
    cachingfsblobstore::DirBlobRef *_base;

    DISALLOW_COPY_AND_ASSIGN(DirBlobRef);
};

}
}

#endif
