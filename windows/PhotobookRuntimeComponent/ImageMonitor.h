#pragma once

#include "ImageMonitor.g.h"

#include "VirtualImagePtr.g.h"
#include "VirtualImagePtr.h"

#include <pb/ImageMonitor.h>

namespace winrt::PhotobookRuntimeComponent::implementation {
struct ImageMonitor : ImageMonitorT<ImageMonitor> {
  ImageMonitor(PB::ImageMonitor &monitor) : mImageMonitor(monitor) {}
  ~ImageMonitor() = default;

  void ReplaceImageMonitorData(
      Windows::Foundation::Collections::IVector<
          Windows::Foundation::Collections::IVector<
              PhotobookRuntimeComponent::VirtualImagePtr>>
                                                                unstagedImages,
      Windows::Foundation::Collections::IVector<winrt::hstring> roots)
  {
    std::vector<std::vector<std::shared_ptr<PB::VirtualImage>>>
                      nativeUnstagedImages;
    std::vector<Path> nativeRoots;

    for (int i = 0; i < (int)unstagedImages.Size(); ++i) {
      std::vector<std::shared_ptr<PB::VirtualImage>> nativeUnstagedLine;
      for (int j = 0; j < (int)unstagedImages.GetAt(i).Size(); ++j) {
        auto nativeImagePtr =
            winrt::get_self<winrt::PhotobookRuntimeComponent::implementation::
                                VirtualImagePtr>(
                unstagedImages.GetAt(i).GetAt(j))
                ->unwrap();
        nativeUnstagedLine.push_back(nativeImagePtr);
      }
      nativeUnstagedImages.push_back(nativeUnstagedLine);
    }

    for (int i = 0; i < (int)roots.Size(); ++i) {
      auto nativeRoot = winrt::to_string(roots.GetAt(i));
      nativeRoots.push_back(nativeRoot);
    }
    mImageMonitor.replaceImageMonitorData(nativeUnstagedImages, nativeRoots);
  }

  void AddRow(winrt::hstring path,
              Windows::Foundation::Collections::IVector<
                  PhotobookRuntimeComponent::VirtualImagePtr>
                  images)
  {
    std::vector<std::shared_ptr<PB::VirtualImage>> nativeUnstagedImages;

    for (int i = 0; i < (int)images.Size(); ++i) {

      auto nativeImagePtr =
          winrt::get_self<winrt::PhotobookRuntimeComponent::implementation::
                              VirtualImagePtr>(images.GetAt(i))
              ->unwrap();
      nativeUnstagedImages.push_back(nativeImagePtr);
    }
    PBDev::Path nativePath = winrt::to_string(path);
    mImageMonitor.addRow(nativePath, nativeUnstagedImages);
  }

  void RemoveRowByIndex(int index) { mImageMonitor.removeRow(index); }

  void RemoveRowByPath(winrt::hstring path)
  {
    PBDev::Path nativePath = winrt::to_string(path);
    mImageMonitor.removeRow(nativePath);
  }

  void Clear() { mImageMonitor.clear(); }

  void CompleteRow(int index) { mImageMonitor.completeRow(index); }
  bool IsPendingByPath(winrt::hstring path)
  {
    PBDev::Path nativePath = winrt::to_string(path);
    return mImageMonitor.isPending(nativePath);
  }
  bool IsPendingByIndex(int index) { return mImageMonitor.isPending(index); }

  unsigned ImportListSize() { return mImageMonitor.importListSize(); }
  unsigned RowSize(unsigned row) { return mImageMonitor.rowSize(row); }
  unsigned RowIndex(winrt::hstring path)
  {
    PBDev::Path nativePath = winrt::to_string(path);
    return mImageMonitor.rowIndex(nativePath);
  }
  bool ContainsRow(winrt::hstring path, bool subPath)
  {
    PBDev::Path nativePath = winrt::to_string(path);
    return mImageMonitor.containsRow(nativePath, subPath);
  }
  winrt::hstring RowPath(unsigned row)
  {
    return winrt::to_hstring(mImageMonitor.rowPath(row).string());
  }

  Windows::Foundation::Collections::IVector<winrt::hstring> RowList()
  {
    auto managedRowList = winrt::single_threaded_vector<winrt::hstring>();

    auto nativeRowList = mImageMonitor.rowList();

    for (auto i = 0; i < (int)nativeRowList.size(); ++i) {
      managedRowList.Append(winrt::to_hstring(nativeRowList.at(i).string()));
    }

    return managedRowList;
  }

  PhotobookRuntimeComponent::VirtualImagePtr Image(unsigned row, unsigned index)
  {
    auto imagePtr = mImageMonitor.image(row, index);
    return winrt::make<VirtualImagePtr>(imagePtr);
  }
  PhotobookRuntimeComponent::VirtualImagePtr Image(winrt::hstring full)
  {
    auto imagePtr = mImageMonitor.image(winrt::to_string(full));
    return winrt::make<VirtualImagePtr>(imagePtr);
  }
  // std::pair<Int32, Int32>       position(Path full) const;

  // std::vector<RowProcessingData> unprocessedImages();

  Windows::Foundation::Collections::IVector<
      Windows::Foundation::Collections::IVector<
          PhotobookRuntimeComponent::VirtualImagePtr>>
  Unstaged()
  {
    auto managedUnstagedImages =
        winrt::single_threaded_vector<Windows::Foundation::Collections::IVector<
            PhotobookRuntimeComponent::VirtualImagePtr>>();

    auto nativeUnstagedImages = mImageMonitor.unstaged();

    for (int i = 0; i < (int)nativeUnstagedImages.size(); ++i) {
      auto managedUnstagedImagesLine = winrt::single_threaded_vector<
          PhotobookRuntimeComponent::VirtualImagePtr>();
      for (int j = 0; j < (int)nativeUnstagedImages.at(i).size(); ++j) {
        auto managedImage =
            winrt::make<VirtualImagePtr>(nativeUnstagedImages.at(i).at(j));
        managedUnstagedImagesLine.Append(managedImage);
      }
      managedUnstagedImages.Append(managedUnstagedImagesLine);
    }
    return managedUnstagedImages;
  }

private:
  PB::ImageMonitor &mImageMonitor;
};
} // namespace winrt::PhotobookRuntimeComponent::implementation