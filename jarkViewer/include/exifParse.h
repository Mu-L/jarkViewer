#pragma once

#include "Utils.h"
#include "exiv2/exiv2.hpp"

class ExifParse{
public:
    static std::string getSimpleInfo(const wstring& path, int width, int height, const uint8_t* buf, size_t fileSize) {
        return (path.ends_with(L".ico") || (width == 0 && height == 0)) ?
            std::format("路径: {}\n大小: {}\n",
                Utils::wstringToUtf8(path), Utils::size2Str(fileSize)) :
            std::format("路径: {}\n大小: {}\n分辨率: {}x{}",
                Utils::wstringToUtf8(path), Utils::size2Str(fileSize), width, height);
    }

    static string handleMathDiv(const string& str) {
        if (str.empty())return "";

        int divIdx = -1;
        bool isNegative = (str[0] == '-');
        for (int i = isNegative ? 1 : 0; i < str.length(); i++) {
            int c = str[i];
            if ('0' <= c && c <= '9') {
                continue;
            }
            else if (c == '/') {
                if (divIdx == -1) {
                    divIdx = i;
                    continue;
                }
                else {
                    divIdx = -1;
                    break;
                }
            }
            else {
                divIdx = -1;
                break;
            }
        }

        if (divIdx > 0) {
            auto a = std::stoll(str.substr(0, divIdx));
            auto b = std::stoll(str.substr((size_t)divIdx + 1));

            if (isNegative)
                a = 0 - a;

            auto resStr = std::format("{:.2f}", (double)a / b);

            if (resStr.ends_with(".00"))
                resStr = resStr.substr(0, resStr.size() - 3);

            return resStr;
        }
        return "";
    }

    static std::string exifDataToString(const std::wstring& path, const Exiv2::ExifData& exifData) {
        if (exifData.empty()) {
            Utils::log("No EXIF data {}", Utils::wstringToUtf8(path));
            return "";
        }

        std::ostringstream oss;
        std::ostringstream ossEnd;

        for (const auto& tag : exifData) {
            const std::string& tagName = tag.key();
            std::string translatedTagName;
            bool toEnd;
            if (tagName.starts_with("Exif.SubImage")) {
                toEnd = true;
                string tag = "Exif.Image" + tagName.substr(14);
                translatedTagName = exifTagsMap.contains(tag) ?
                    ("子图" + tagName.substr(13, 2) + exifTagsMap.at(tag)) :
                    ("子图" + tagName.substr(13));
            }
            else if (tagName.starts_with("Exif.Thumbnail")) {
                toEnd = true;
                string tag = "Exif.Image" + tagName.substr(14);
                translatedTagName = exifTagsMap.contains(tag) ?
                    ("缩略图." + exifTagsMap.at(tag)) :
                    ("缩略图" + tagName.substr(14));
            }
            else if (tagName.starts_with("Exif.Nikon")) {
                toEnd = true;
                translatedTagName = "尼康" + tagName.substr(10);
            }
            else if (tagName.starts_with("Exif.CanonCs")) {
                toEnd = true;
                string tag = "Exif.Image" + tagName.substr(12);
                if (!exifTagsMap.contains(tag))tag = "Exif.Photo" + tagName.substr(12);
                translatedTagName = exifTagsMap.contains(tag) ?
                    ("佳能Cs." + exifTagsMap.at(tag)) :
                    ("佳能Cs." + tagName.substr(13));
            }
            else if (tagName.starts_with("Exif.CanonSi")) {
                toEnd = true;
                string tag = "Exif.Image" + tagName.substr(12);
                if (!exifTagsMap.contains(tag))tag = "Exif.Photo" + tagName.substr(12);
                translatedTagName = exifTagsMap.contains(tag) ?
                    ("佳能Si." + exifTagsMap.at(tag)) :
                    ("佳能Si." + tagName.substr(13));
            }
            else if (tagName.starts_with("Exif.CanonPi")) {
                toEnd = true;
                string tag = "Exif.Image" + tagName.substr(12);
                if (!exifTagsMap.contains(tag))tag = "Exif.Photo" + tagName.substr(12);
                translatedTagName = exifTagsMap.contains(tag) ?
                    ("佳能Pi." + exifTagsMap.at(tag)) :
                    ("佳能Pi." + tagName.substr(13));
            }
            else if (tagName.starts_with("Exif.CanonPa")) {
                toEnd = true;
                string tag = "Exif.Image" + tagName.substr(12);
                if (!exifTagsMap.contains(tag))tag = "Exif.Photo" + tagName.substr(12);
                translatedTagName = exifTagsMap.contains(tag) ?
                    ("佳能Pa." + exifTagsMap.at(tag)) :
                    ("佳能Pa." + tagName.substr(13));
            }
            else if (tagName.starts_with("Exif.Canon")) {
                toEnd = true;
                string tag = "Exif.Image" + tagName.substr(10);
                if (!exifTagsMap.contains(tag))tag = "Exif.Photo" + tagName.substr(10);
                translatedTagName = exifTagsMap.contains(tag) ?
                    ("佳能." + exifTagsMap.at(tag)) :
                    ("佳能." + tagName.substr(11));
            }
            else if (tagName.starts_with("Exif.Pentax")) {
                toEnd = true;
                string tag = "Exif.Image" + tagName.substr(11);
                if (!exifTagsMap.contains(tag))tag = "Exif.Photo" + tagName.substr(11);
                translatedTagName = exifTagsMap.contains(tag) ?
                    ("宾得." + exifTagsMap.at(tag)) :
                    ("宾得." + tagName.substr(12));
            }
            else if (tagName.starts_with("Exif.Fujifilm")) {
                toEnd = true;
                string tag = "Exif.Image" + tagName.substr(13);
                if (!exifTagsMap.contains(tag))tag = "Exif.Photo" + tagName.substr(13);
                translatedTagName = exifTagsMap.contains(tag) ?
                    ("富士." + exifTagsMap.at(tag)) :
                    ("富士." + tagName.substr(14));
            }
            else if (tagName.starts_with("Exif.Olympus")) {
                toEnd = true;
                string tag = "Exif.Image" + tagName.substr(12);
                if (!exifTagsMap.contains(tag))tag = "Exif.Photo" + tagName.substr(12);
                translatedTagName = exifTagsMap.contains(tag) ?
                    ("奥林巴斯." + exifTagsMap.at(tag)) :
                    ("奥林巴斯." + tagName.substr(13));
            }
            else if (tagName.starts_with("Exif.Panasonic")) {
                toEnd = true;
                string tag = "Exif.Image" + tagName.substr(14);
                if (!exifTagsMap.contains(tag))tag = "Exif.Photo" + tagName.substr(14);
                translatedTagName = exifTagsMap.contains(tag) ?
                    ("松下." + exifTagsMap.at(tag)) :
                    ("松下." + tagName.substr(15));
            }
            else if (tagName.starts_with("Exif.Sony1")) {
                toEnd = true;
                string tag = "Exif.Image" + tagName.substr(10);
                if (!exifTagsMap.contains(tag))tag = "Exif.Photo" + tagName.substr(10);
                translatedTagName = exifTagsMap.contains(tag) ?
                    ("索尼." + exifTagsMap.at(tag)) :
                    ("索尼." + tagName.substr(11));
            }
            else {
                toEnd = false;
                translatedTagName = exifTagsMap.contains(tagName) ? exifTagsMap.at(tagName) : tagName;
            }

            std::string tagValue;
            if (tag.typeId() == Exiv2::TypeId::undefined || tagName == "Exif.Image.XMLPacket") {
                auto tmp = tag.toString();
                std::istringstream iss(tmp);
                std::string result;
                int number;
                while (iss >> number) {
                    if (number < ' ' || number > 127)
                        break;
                    result += static_cast<char>(number);
                }
                tagValue = result.empty() ? tmp : result + " [" + tmp + "]";
            }
            else {
                tagValue = tag.toString();
            }

            if (tagName == "Exif.GPSInfo.GPSLatitudeRef" || tagName == "Exif.GPSInfo.GPSLongitudeRef") {
                if (tagValue.length() > 0) {
                    switch (tagValue[0])
                    {
                    case 'N':tagValue = "北纬 " + tagValue; break;
                    case 'S':tagValue = "南纬 " + tagValue; break;
                    case 'E':tagValue = "东经 " + tagValue; break;
                    case 'W':tagValue = "西经 " + tagValue; break;
                    }
                }
            }

            if (tagName == "Exif.Photo.MakerNote") {
                if (tagValue.length() > 0 && tagValue.starts_with("Apple iOS")) {
                    tagValue = "Apple IOS";
                }
            }

            if (tagName == "Exif.GPSInfo.GPSLatitude" || tagName == "Exif.GPSInfo.GPSLongitude") {
                auto firstSpaceIdx = tagValue.find_first_of(' ');
                auto secondSpaceIdx = tagValue.find_last_of(' ');
                if (firstSpaceIdx != string::npos && secondSpaceIdx != string::npos && firstSpaceIdx < secondSpaceIdx) {
                    auto n1 = handleMathDiv(tagValue.substr(0, firstSpaceIdx));
                    auto n2 = handleMathDiv(tagValue.substr(firstSpaceIdx + 1, secondSpaceIdx - firstSpaceIdx - 1));
                    auto n3 = handleMathDiv(tagValue.substr(secondSpaceIdx + 1));
                    tagValue = std::format("{}°{}' {}'' ({})", n1, n2, n3, tagValue);
                }
            }
            else if (tagName == "Exif.GPSInfo.GPSTimeStamp") {
                auto firstSpaceIdx = tagValue.find_first_of(' ');
                auto secondSpaceIdx = tagValue.find_last_of(' ');
                if (firstSpaceIdx != string::npos && secondSpaceIdx != string::npos && firstSpaceIdx < secondSpaceIdx) {
                    auto n1 = handleMathDiv(tagValue.substr(0, firstSpaceIdx));
                    auto n2 = handleMathDiv(tagValue.substr(firstSpaceIdx + 1, secondSpaceIdx - firstSpaceIdx - 1));
                    auto n3 = handleMathDiv(tagValue.substr(secondSpaceIdx + 1));
                    tagValue = std::format("{}:{}:{} ({})", n1, n2, n3, tagValue);
                }
            }
            else if (tagName == "Exif.Photo.UserComment") { // 可能包含AI生图prompt信息
                auto a = tag.value().clone();
                vector<uint8_t> buf(a->size());
                a->copy(buf.data(), Exiv2::ByteOrder::bigEndian);
                if (!memcmp(buf.data(), "UNICODE\0", 8)) {
                    wstring str((wchar_t*)(buf.data() + 8), (buf.size() - 8) / 2);
                    tagValue = Utils::wstringToUtf8(str);
                    auto idx = tagValue.find("\nNegative prompt");
                    if (idx != string::npos) {
                        tagValue.replace(idx, 16, "\n\n反提示词");
                        tagValue = "\n\n正提示词: " + tagValue;
                    }

                    idx = tagValue.find("\nSteps:");
                    if (idx != string::npos) {
                        tagValue.replace(idx, 7, "\n\n参数: Steps:");
                    }
                }
            }
            else if (2 < tagValue.length() && tagValue.length() < 100) {
                auto res = handleMathDiv(tagValue);
                if (!res.empty())
                    tagValue = std::format("{} ({})", res, tagValue);
            }

            string tmp;
            if (tagName == "Exif.Photo.UserComment")
                tmp = "\n" + translatedTagName + ": " + tagValue;
            else
                tmp = "\n" + translatedTagName + ": " + (tagValue.length() < 100 ? tagValue :
                    tagValue.substr(0, 100) + std::format(" ...] length:{}", tagValue.length()));

            if (toEnd)ossEnd << tmp;
            else oss << tmp;
        }

        return oss.str() + ossEnd.str();
    }

    static std::string xmpDataToString(const std::wstring& path, const Exiv2::XmpData& xmpData) {
        if (xmpData.empty()) {
            Utils::log("No XMP data {}", Utils::wstringToUtf8(path));
            return "";
        }

        string xmpStr = "\n\nXmp Data:";
        for (const auto& tag : xmpData) {
            xmpStr += "\n"+tag.key() + ": " + tag.value().toString();
        }
        return xmpStr;
    }

    static std::string iptcDataToString(const std::wstring& path, const Exiv2::IptcData& IptcData) {
        if (IptcData.empty()) {
            Utils::log("No Iptc data {}", Utils::wstringToUtf8(path));
            return "";
        }

        string itpcStr = "\n\nIptc Data:";
        for (const auto& tag : IptcData) {
            itpcStr += "\n" + tag.key() + ": " + tag.value().toString();
        }
        return itpcStr;
    }

    static string AI_Prompt(const std::wstring& path, const uint8_t* buf) {
        if (!strncmp((const char*)buf + 0x25, "tEXtparameters", 14)) {
            int length = (buf[0x21] << 24) + (buf[0x22] << 16) + (buf[0x23] << 8) + buf[0x24];
            if (length > 16 * 1024) {
                return "";
            }

            string prompt((const char*)buf + 0x29, length); // format: Windows-1252  ISO/IEC 8859-1（Latin-1）

            prompt = Utils::wstringToUtf8(Utils::latin1ToWstring(prompt));

            auto idx = prompt.find("parameters");
            if (idx != string::npos) {
                prompt.replace(idx, 11, "\n正提示词: ");
            }
            else {
                prompt = "\n正提示词: " + prompt;
            }

            idx = prompt.find("Negative prompt");
            if (idx != string::npos) {
                prompt.replace(idx, 16, "\n反提示词: ");
            }

            idx = prompt.find("\nSteps:");
            if (idx != string::npos) {
                prompt.replace(idx, 7, "\n\n参数: Steps:");
            }

            return "\nAI生图提示词 Prompt:\n" + prompt;
        }
        else if (!strncmp((const char*)buf + 0x25, "iTXtparameters", 14)) {
            int length = (buf[0x21] << 24) + (buf[0x22] << 16) + (buf[0x23] << 8) + buf[0x24];
            if (length > 16 * 1024) {
                return "";
            }

            string prompt((const char*)buf + 0x38, length - 15); // format: Windows-1252  ISO/IEC 8859-1（Latin-1）

            prompt = Utils::wstringToUtf8(Utils::latin1ToWstring(prompt));

            auto idx = prompt.find("parameters");
            if (idx != string::npos) {
                prompt.replace(idx, 11, "\n正提示词: ");
            }
            else {
                prompt = "\n正提示词: " + prompt;
            }

            idx = prompt.find("\nNegative prompt");
            if (idx != string::npos) {
                prompt.replace(idx, 16, "\n\n反提示词: ");
            }

            idx = prompt.find("\nSteps:");
            if (idx != string::npos) {
                prompt.replace(idx, 7, "\n\n参数: Steps:");
            }

            return "\nAI生图提示词 Prompt:\n" + prompt;
        }
        else if (!strncmp((const char*)buf + 0x25, "tEXtprompt", 10)) {

            int length = (buf[0x21] << 24) + (buf[0x22] << 16) + (buf[0x23] << 8) + buf[0x24];
            if (length > 16 * 1024) {
                return "";
            }

            string prompt((const char*)buf + 0x29 + 7, length - 7); // format: Windows-1252  ISO/IEC 8859-1（Latin-1）

            prompt = Utils::wstringToUtf8(Utils::latin1ToWstring(prompt));

            return "\nAI生图提示词 Prompt:\n" + prompt;
        }

        return "";
    }

    static std::string getExif(const std::wstring& path, const uint8_t* buf, int fileSize) {
        try {
            auto image = Exiv2::ImageFactory::open(buf, fileSize);
            image->readMetadata();

            auto exifStr = exifDataToString(path, image->exifData());
            auto xmpStr = xmpDataToString(path, image->xmpData());
            auto iptcStr = iptcDataToString(path, image->iptcData());
            string prompt = AI_Prompt(path, buf);

            if ((exifStr.length() + xmpStr.length() + iptcStr.length() + prompt.length()) > 0)
                return  "\n\n【按 C 键复制图像全部信息】\n" + exifStr + xmpStr + iptcStr + prompt;
            else
                return "";
        }
        catch (Exiv2::Error& e) {
            Utils::log("Caught Exiv2 exception {}\n{}", Utils::wstringToUtf8(path), e.what());
            return "";
        }
        return "";
    }

private:

    // https://exiv2.org/tags.html
    // https://www.colorpilot.com/exiftable-thumbnail.html
    // https://exiftool.org/TagNames/PNG.html
    // https://exiftool.org/TagNames/Canon.html
    static inline const std::unordered_map<std::string, std::string> exifTagsMap{
        { "Exif.Image.0x9a00", "设备" },
        { "Exif.Image.ProcessingSoftware", "处理软件" },
        { "Exif.Image.NewSubfileType", "新子文件类型" },
        { "Exif.Image.SubfileType", "子文件类型" },
        { "Exif.Image.ImageWidth", "图像宽度" },
        { "Exif.Image.ImageLength", "图像长度" },
        { "Exif.Image.BitsPerSample", "每个样本的位数" },
        { "Exif.Image.Compression", "压缩" },
        { "Exif.Image.PhotometricInterpretation", "光度解释" },
        { "Exif.Image.Thresholding", "阈值处理" },
        { "Exif.Image.CellWidth", "单元格宽度" },
        { "Exif.Image.CellLength", "单元格长度" },
        { "Exif.Image.FillOrder", "填充顺序" },
        { "Exif.Image.DocumentName", "文档名称" },
        { "Exif.Image.ImageDescription", "图像描述" },
        { "Exif.Image.Make", "制造商" },
        { "Exif.Image.Model", "型号" },
        { "Exif.Image.StripOffsets", "条带偏移量" },
        { "Exif.Image.Orientation", "方向" },
        { "Exif.Image.SamplesPerPixel", "每像素样本数" },
        { "Exif.Image.RowsPerStrip", "每条带行数" },
        { "Exif.Image.StripByteCounts", "条带字节数" },
        { "Exif.Image.XResolution", "X分辨率" },
        { "Exif.Image.YResolution", "Y分辨率" },
        { "Exif.Image.PlanarConfiguration", "平面配置" },
        { "Exif.Image.PageName", "页面名称" },
        { "Exif.Image.XPosition", "X位置" },
        { "Exif.Image.YPosition", "Y位置" },
        { "Exif.Image.GrayResponseUnit", "灰度响应单位" },
        { "Exif.Image.GrayResponseCurve", "灰度响应曲线" },
        { "Exif.Image.T4Options", "T4选项" },
        { "Exif.Image.T6Options", "T6选项" },
        { "Exif.Image.ResolutionUnit", "分辨率单位" },
        { "Exif.Image.PageNumber", "页码" },
        { "Exif.Image.TransferFunction", "传输函数" },
        { "Exif.Image.Software", "软件" },
        { "Exif.Image.DateTime", "日期时间" },
        { "Exif.Image.Artist", "艺术家" },
        { "Exif.Image.HostComputer", "主机计算机" },
        { "Exif.Image.Predictor", "预测器" },
        { "Exif.Image.WhitePoint", "白点" },
        { "Exif.Image.PrimaryChromaticities", "原色色度" },
        { "Exif.Image.ColorMap", "颜色映射" },
        { "Exif.Image.HalftoneHints", "半色调提示" },
        { "Exif.Image.TileWidth", "瓦片宽度" },
        { "Exif.Image.TileLength", "瓦片长度" },
        { "Exif.Image.TileOffsets", "瓦片偏移量" },
        { "Exif.Image.TileByteCounts", "瓦片字节数" },
        { "Exif.Image.SubIFDs", "子IFDs" },
        { "Exif.Image.InkSet", "墨水集" },
        { "Exif.Image.InkNames", "墨水名称" },
        { "Exif.Image.NumberOfInks", "墨水数量" },
        { "Exif.Image.DotRange", "点范围" },
        { "Exif.Image.TargetPrinter", "目标打印机" },
        { "Exif.Image.ExtraSamples", "额外样本" },
        { "Exif.Image.SampleFormat", "样本格式" },
        { "Exif.Image.SMinSampleValue", "最小样本值" },
        { "Exif.Image.SMaxSampleValue", "最大样本值" },
        { "Exif.Image.TransferRange", "传输范围" },
        { "Exif.Image.ClipPath", "裁剪路径" },
        { "Exif.Image.XClipPathUnits", "X裁剪路径单位" },
        { "Exif.Image.YClipPathUnits", "Y裁剪路径单位" },
        { "Exif.Image.Indexed", "索引" },
        { "Exif.Image.JPEGTables", "JPEG表" },
        { "Exif.Image.OPIProxy", "OPI代理" },
        { "Exif.Image.JPEGProc", "JPEG处理" },
        { "Exif.Image.JPEGInterchangeFormat", "JPEG交换格式" },
        { "Exif.Image.JPEGInterchangeFormatLength", "JPEG交换格式长度" },
        { "Exif.Image.JPEGRestartInterval", "JPEG重启间隔" },
        { "Exif.Image.JPEGLosslessPredictors", "JPEG无损预测器" },
        { "Exif.Image.JPEGPointTransforms", "JPEG点变换" },
        { "Exif.Image.JPEGQTables", "JPEG量化表" },
        { "Exif.Image.JPEGDCTables", "JPEG直流表" },
        { "Exif.Image.JPEGACTables", "JPEG交流表" },
        { "Exif.Image.YCbCrCoefficients", "YCbCr系数" },
        { "Exif.Image.YCbCrSubSampling", "YCbCr子采样" },
        { "Exif.Image.YCbCrPositioning", "YCbCr定位" },
        { "Exif.Image.ReferenceBlackWhite", "参考黑白点" },
        { "Exif.Image.XMLPacket", "XML数据包" },
        { "Exif.Image.Rating", "评分" },
        { "Exif.Image.RatingPercent", "评分百分比" },
        { "Exif.Image.VignettingCorrParams", "暗角校正参数" },
        { "Exif.Image.ChromaticAberrationCorrParams", "色差校正参数" },
        { "Exif.Image.DistortionCorrParams", "畸变校正参数" },
        { "Exif.Image.ImageID", "图像ID" },
        { "Exif.Image.CFARepeatPatternDim", "CFA重复模式尺寸" },
        { "Exif.Image.CFAPattern", "CFA模式" },
        { "Exif.Image.BatteryLevel", "电池电量" },
        { "Exif.Image.Copyright", "版权" },
        { "Exif.Image.ExposureTime", "曝光时间" },
        { "Exif.Image.FNumber", "光圈值" },
        { "Exif.Image.IPTCNAA", "IPTC/NAA" },
        { "Exif.Image.ImageResources", "图像资源" },
        { "Exif.Image.ExifTag", "Exif标签" },
        { "Exif.Image.InterColorProfile", "内部颜色配置文件" },
        { "Exif.Image.ExposureProgram", "曝光程序" },
        { "Exif.Image.SpectralSensitivity", "光谱敏感度" },
        { "Exif.Image.GPSTag", "GPS标签" },
        { "Exif.Image.ISOSpeedRatings", "ISO速度等级" },
        { "Exif.Image.OECF", "光电转换函数" },
        { "Exif.Image.Interlace", "隔行扫描" },
        { "Exif.Image.TimeZoneOffset", "时区偏移" },
        { "Exif.Image.SelfTimerMode", "自拍模式" },
        { "Exif.Image.DateTimeOriginal", "原始日期时间" },
        { "Exif.Image.CompressedBitsPerPixel", "每像素压缩位数" },
        { "Exif.Image.ShutterSpeedValue", "快门速度值" },
        { "Exif.Image.ApertureValue", "光圈值" },
        { "Exif.Image.BrightnessValue", "亮度值" },
        { "Exif.Image.ExposureBiasValue", "曝光补偿值" },
        { "Exif.Image.MaxApertureValue", "最大光圈值" },
        { "Exif.Image.SubjectDistance", "主体距离" },
        { "Exif.Image.MeteringMode", "测光模式" },
        { "Exif.Image.LightSource", "光源" },
        { "Exif.Image.Flash", "闪光灯" },
        { "Exif.Image.FocalLength", "焦距" },
        { "Exif.Image.FlashEnergy", "闪光灯能量" },
        { "Exif.Image.SpatialFrequencyResponse", "空间频率响应" },
        { "Exif.Image.Noise", "噪声" },
        { "Exif.Image.FocalPlaneXResolution", "焦平面X分辨率" },
        { "Exif.Image.FocalPlaneYResolution", "焦平面Y分辨率" },
        { "Exif.Image.FocalPlaneResolutionUnit", "焦平面分辨率单位" },
        { "Exif.Image.ImageNumber", "图像编号" },
        { "Exif.Image.SecurityClassification", "安全分类" },
        { "Exif.Image.ImageHistory", "图像历史" },
        { "Exif.Image.SubjectLocation", "主体位置" },
        { "Exif.Image.ExposureIndex", "曝光指数" },
        { "Exif.Image.TIFFEPStandardID", "TIFF/EP标准ID" },
        { "Exif.Image.SensingMethod", "感应方法" },
        { "Exif.Image.XPTitle", "XP标题" },
        { "Exif.Image.XPComment", "XP注释" },
        { "Exif.Image.XPAuthor", "XP作者" },
        { "Exif.Image.XPKeywords", "XP关键词" },
        { "Exif.Image.XPSubject", "XP主题" },
        { "Exif.Image.PrintImageMatching", "打印图像匹配" },
        { "Exif.Image.DNGVersion", "DNG版本" },
        { "Exif.Image.DNGBackwardVersion", "DNG向后兼容版本" },
        { "Exif.Image.UniqueCameraModel", "唯一相机型号" },
        { "Exif.Image.LocalizedCameraModel", "本地化相机型号" },
        { "Exif.Image.CFAPlaneColor", "CFA平面颜色" },
        { "Exif.Image.CFALayout", "CFA布局" },
        { "Exif.Image.LinearizationTable", "线性化表" },
        { "Exif.Image.BlackLevelRepeatDim", "黑电平重复尺寸" },
        { "Exif.Image.BlackLevel", "黑电平" },
        { "Exif.Image.BlackLevelDeltaH", "水平黑电平增量" },
        { "Exif.Image.BlackLevelDeltaV", "垂直黑电平增量" },
        { "Exif.Image.WhiteLevel", "白电平" },
        { "Exif.Image.DefaultScale", "默认比例" },
        { "Exif.Image.DefaultCropOrigin", "默认裁剪原点" },
        { "Exif.Image.DefaultCropSize", "默认裁剪尺寸" },
        { "Exif.Image.ColorMatrix1", "颜色矩阵1" },
        { "Exif.Image.ColorMatrix2", "颜色矩阵2" },
        { "Exif.Image.CameraCalibration1", "相机校准1" },
        { "Exif.Image.CameraCalibration2", "相机校准2" },
        { "Exif.Image.ReductionMatrix1", "缩减矩阵1" },
        { "Exif.Image.ReductionMatrix2", "缩减矩阵2" },
        { "Exif.Image.AnalogBalance", "模拟平衡" },
        { "Exif.Image.AsShotNeutral", "拍摄时的中性点" },
        { "Exif.Image.AsShotWhiteXY", "拍摄时的白点XY坐标" },
        { "Exif.Image.BaselineExposure", "基准曝光" },
        { "Exif.Image.BaselineNoise", "基准噪声" },
        { "Exif.Image.BaselineSharpness", "基准锐度" },
        { "Exif.Image.BayerGreenSplit", "拜耳绿色分离" },
        { "Exif.Image.LinearResponseLimit", "线性响应限制" },
        { "Exif.Image.CameraSerialNumber", "相机序列号" },
        { "Exif.Image.LensInfo", "镜头信息" },
        { "Exif.Image.ChromaBlurRadius", "色度模糊半径" },
        { "Exif.Image.AntiAliasStrength", "抗锯齿强度" },
        { "Exif.Image.ShadowScale", "阴影比例" },
        { "Exif.Image.DNGPrivateData", "DNG私有数据" },
        { "Exif.Image.CalibrationIlluminant1", "校准光源1" },
        { "Exif.Image.CalibrationIlluminant2", "校准光源2" },
        { "Exif.Image.BestQualityScale", "最佳质量比例" },
        { "Exif.Image.RawDataUniqueID", "原始数据唯一ID" },
        { "Exif.Image.OriginalRawFileName", "原始RAW文件名" },
        { "Exif.Image.OriginalRawFileData", "原始RAW文件数据" },
        { "Exif.Image.ActiveArea", "有效区域" },
        { "Exif.Image.MaskedAreas", "遮罩区域" },
        { "Exif.Image.AsShotICCProfile", "拍摄时的ICC配置文件" },
        { "Exif.Image.AsShotPreProfileMatrix", "拍摄时的预配置文件矩阵" },
        { "Exif.Image.CurrentICCProfile", "当前ICC配置文件" },
        { "Exif.Image.CurrentPreProfileMatrix", "当前预配置文件矩阵" },
        { "Exif.Image.ColorimetricReference", "比色参考" },
        { "Exif.Image.CameraCalibrationSignature", "相机校准签名" },
        { "Exif.Image.ProfileCalibrationSignature", "配置文件校准签名" },
        { "Exif.Image.ExtraCameraProfiles", "额外相机配置文件" },
        { "Exif.Image.AsShotProfileName", "拍摄时配置文件名称" },
        { "Exif.Image.NoiseReductionApplied", "已应用的降噪" },
        { "Exif.Image.ProfileName", "配置文件名称" },
        { "Exif.Image.ProfileHueSatMapDims", "配置文件色相饱和度映射维度" },
        { "Exif.Image.ProfileHueSatMapData1", "配置文件色相饱和度映射数据1" },
        { "Exif.Image.ProfileHueSatMapData2", "配置文件色相饱和度映射数据2" },
        { "Exif.Image.ProfileToneCurve", "配置文件色调曲线" },
        { "Exif.Image.ProfileEmbedPolicy", "配置文件嵌入策略" },
        { "Exif.Image.ProfileCopyright", "配置文件版权" },
        { "Exif.Image.ForwardMatrix1", "前向矩阵1" },
        { "Exif.Image.ForwardMatrix2", "前向矩阵2" },
        { "Exif.Image.PreviewApplicationName", "预览应用程序名称" },
        { "Exif.Image.PreviewApplicationVersion", "预览应用程序版本" },
        { "Exif.Image.PreviewSettingsName", "预览设置名称" },
        { "Exif.Image.PreviewSettingsDigest", "预览设置摘要" },
        { "Exif.Image.PreviewColorSpace", "预览色彩空间" },
        { "Exif.Image.PreviewDateTime", "预览日期时间" },
        { "Exif.Image.RawImageDigest", "原始图像摘要" },
        { "Exif.Image.OriginalRawFileDigest", "原始RAW文件摘要" },
        { "Exif.Image.SubTileBlockSize", "子块大小" },
        { "Exif.Image.RowInterleaveFactor", "行交错因子" },
        { "Exif.Image.ProfileLookTableDims", "配置文件查找表维度" },
        { "Exif.Image.ProfileLookTableData", "配置文件查找表数据" },
        { "Exif.Image.OpcodeList1", "操作码列表1" },
        { "Exif.Image.OpcodeList2", "操作码列表2" },
        { "Exif.Image.OpcodeList3", "操作码列表3" },
        { "Exif.Image.NoiseProfile", "噪声配置文件" },
        { "Exif.Image.TimeCodes", "时间码" },
        { "Exif.Image.FrameRate", "帧率" },
        { "Exif.Image.TStop", "T档" },
        { "Exif.Image.ReelName", "胶片名称" },
        { "Exif.Image.CameraLabel", "相机标签" },
        { "Exif.Image.OriginalDefaultFinalSize", "原始默认最终尺寸" },
        { "Exif.Image.OriginalBestQualityFinalSize", "原始最佳质量最终尺寸" },
        { "Exif.Image.OriginalDefaultCropSize", "原始默认裁剪尺寸" },
        { "Exif.Image.ProfileHueSatMapEncoding", "配置文件色相饱和度映射编码" },
        { "Exif.Image.ProfileLookTableEncoding", "配置文件查找表编码" },
        { "Exif.Image.BaselineExposureOffset", "基准曝光偏移" },
        { "Exif.Image.DefaultBlackRender", "默认黑色渲染" },
        { "Exif.Image.NewRawImageDigest", "新原始图像摘要" },
        { "Exif.Image.RawToPreviewGain", "原始到预览增益" },
        { "Exif.Image.DefaultUserCrop", "默认用户裁剪" },
        { "Exif.Image.DepthFormat", "深度格式" },
        { "Exif.Image.DepthNear", "近深度" },
        { "Exif.Image.DepthFar", "远深度" },
        { "Exif.Image.DepthUnits", "深度单位" },
        { "Exif.Image.DepthMeasureType", "深度测量类型" },
        { "Exif.Image.EnhanceParams", "增强参数" },
        { "Exif.Image.ProfileGainTableMap", "配置文件增益表映射" },
        { "Exif.Image.SemanticName", "语义名称" },
        { "Exif.Image.SemanticInstanceID", "语义实例ID" },
        { "Exif.Image.CalibrationIlluminant3", "校准光源3" },
        { "Exif.Image.CameraCalibration3", "相机校准3" },
        { "Exif.Image.ColorMatrix3", "颜色矩阵3" },
        { "Exif.Image.ForwardMatrix3", "前向矩阵3" },
        { "Exif.Image.IlluminantData1", "光源数据1" },
        { "Exif.Image.IlluminantData2", "光源数据2" },
        { "Exif.Image.IlluminantData3", "光源数据3" },
        { "Exif.Image.MaskSubArea", "遮罩子区域" },
        { "Exif.Image.ProfileHueSatMapData3", "配置文件色相饱和度映射数据3" },
        { "Exif.Image.ReductionMatrix3", "缩减矩阵3" },
        { "Exif.Image.RGBTables", "RGB表" },
        { "Exif.Image.ProfileGainTableMap2", "配置文件增益表映射2" },
        { "Exif.Image.ColumnInterleaveFactor", "列交错因子" },
        { "Exif.Image.ImageSequenceInfo", "图像序列信息" },
        { "Exif.Image.ImageStats", "图像统计" },
        { "Exif.Image.ProfileDynamicRange", "配置文件动态范围" },
        { "Exif.Image.ProfileGroupName", "配置文件组名称" },
        { "Exif.Image.JXLDistance", "JXL距离" },
        { "Exif.Image.JXLEffort", "JXL努力程度" },
        { "Exif.Image.JXLDecodeSpeed", "JXL解码速度" },
        { "Exif.Image.MakerNoteSafety", "制造商备注安全性" },
        { "Exif.Photo.ExposureTime", "曝光时间" },
        { "Exif.Photo.FNumber", "光圈值" },
        { "Exif.Photo.ExposureProgram", "曝光程序" },
        { "Exif.Photo.SpectralSensitivity", "光谱敏感度" },
        { "Exif.Photo.ISOSpeedRatings", "ISO感光度" },
        { "Exif.Photo.OECF", "光电转换函数" },
        { "Exif.Photo.SensitivityType", "感光度类型" },
        { "Exif.Photo.StandardOutputSensitivity", "标准输出感光度" },
        { "Exif.Photo.RecommendedExposureIndex", "推荐曝光指数" },
        { "Exif.Photo.ISOSpeed", "ISO速度" },
        { "Exif.Photo.ISOSpeedLatitudeyyy", "ISO速度纬度yyy" },
        { "Exif.Photo.ISOSpeedLatitudezzz", "ISO速度纬度zzz" },
        { "Exif.Photo.ExifVersion", "Exif版本" },
        { "Exif.Photo.DateTimeOriginal", "原始日期时间" },
        { "Exif.Photo.DateTimeDigitized", "数字日期时间" },
        { "Exif.Photo.OffsetTime", "偏移时间" },
        { "Exif.Photo.OffsetTimeOriginal", "原始偏移时间" },
        { "Exif.Photo.OffsetTimeDigitized", "数字偏移时间" },
        { "Exif.Photo.ComponentsConfiguration", "组件配置" },
        { "Exif.Photo.CompressedBitsPerPixel", "每像素压缩位数" },
        { "Exif.Photo.ShutterSpeedValue", "快门速度值" },
        { "Exif.Photo.ApertureValue", "光圈值" },
        { "Exif.Photo.BrightnessValue", "亮度值" },
        { "Exif.Photo.ExposureBiasValue", "曝光补偿值" },
        { "Exif.Photo.MaxApertureValue", "最大光圈值" },
        { "Exif.Photo.SubjectDistance", "主体距离" },
        { "Exif.Photo.MeteringMode", "测光模式" },
        { "Exif.Photo.LightSource", "光源" },
        { "Exif.Photo.Flash", "闪光灯" },
        { "Exif.Photo.FocalLength", "焦距" },
        { "Exif.Photo.SubjectArea", "主体区域" },
        { "Exif.Photo.UserComment", "用户评论" },
        { "Exif.Photo.SubSecTime", "亚秒时间" },
        { "Exif.Photo.SubSecTimeOriginal", "原始亚秒时间" },
        { "Exif.Photo.SubSecTimeDigitized", "数字亚秒时间" },
        { "Exif.Photo.Temperature", "温度" },
        { "Exif.Photo.Humidity", "湿度" },
        { "Exif.Photo.Pressure", "压力" },
        { "Exif.Photo.WaterDepth", "水深" },
        { "Exif.Photo.Acceleration", "加速度" },
        { "Exif.Photo.CameraElevationAngle", "相机仰角" },
        { "Exif.Photo.FlashpixVersion", "Flashpix版本" },
        { "Exif.Photo.ColorSpace", "色彩空间" },
        { "Exif.Photo.PixelXDimension", "像素X维度" },
        { "Exif.Photo.PixelYDimension", "像素Y维度" },
        { "Exif.Photo.RelatedSoundFile", "相关音频文件" },
        { "Exif.Photo.InteroperabilityTag", "互操作性标签" },
        { "Exif.Photo.FlashEnergy", "闪光灯能量" },
        { "Exif.Photo.SpatialFrequencyResponse", "空间频率响应" },
        { "Exif.Photo.FocalPlaneXResolution", "焦平面X分辨率" },
        { "Exif.Photo.FocalPlaneYResolution", "焦平面Y分辨率" },
        { "Exif.Photo.FocalPlaneResolutionUnit", "焦平面分辨率单位" },
        { "Exif.Photo.SubjectLocation", "主体位置" },
        { "Exif.Photo.ExposureIndex", "曝光指数" },
        { "Exif.Photo.SensingMethod", "感应方法" },
        { "Exif.Photo.FileSource", "文件源" },
        { "Exif.Photo.SceneType", "场景类型" },
        { "Exif.Photo.CFAPattern", "CFA模式" },
        { "Exif.Photo.CustomRendered", "自定义渲染" },
        { "Exif.Photo.ExposureMode", "曝光模式" },
        { "Exif.Photo.WhiteBalance", "白平衡" },
        { "Exif.Photo.DigitalZoomRatio", "数字变焦比例" },
        { "Exif.Photo.FocalLengthIn35mmFilm", "35mm胶片等效焦距" },
        { "Exif.Photo.SceneCaptureType", "场景拍摄类型" },
        { "Exif.Photo.GainControl", "增益控制" },
        { "Exif.Photo.Contrast", "对比度" },
        { "Exif.Photo.Saturation", "饱和度" },
        { "Exif.Photo.Sharpness", "锐度" },
        { "Exif.Photo.DeviceSettingDescription", "设备设置描述" },
        { "Exif.Photo.SubjectDistanceRange", "主体距离范围" },
        { "Exif.Photo.ImageUniqueID", "图像唯一ID" },
        { "Exif.Photo.CameraOwnerName", "相机所有者名称" },
        { "Exif.Photo.BodySerialNumber", "机身序列号" },
        { "Exif.Photo.LensSpecification", "镜头规格" },
        { "Exif.Photo.LensMake", "镜头制造商" },
        { "Exif.Photo.LensModel", "镜头型号" },
        { "Exif.Photo.LensSerialNumber", "镜头序列号" },
        { "Exif.Photo.ImageTitle", "图像标题" },
        { "Exif.Photo.Photographer", "摄影师" },
        { "Exif.Photo.ImageEditor", "图像编辑器" },
        { "Exif.Photo.CameraFirmware", "相机固件" },
        { "Exif.Photo.RAWDevelopingSoftware", "RAW处理软件" },
        { "Exif.Photo.ImageEditingSoftware", "图像编辑软件" },
        { "Exif.Photo.MetadataEditingSoftware", "元数据编辑软件" },
        { "Exif.Photo.CompositeImage", "合成图像" },
        { "Exif.Photo.SourceImageNumberOfCompositeImage", "合成图像的源图像数量" },
        { "Exif.Photo.SourceExposureTimesOfCompositeImage", "合成图像的源曝光时间" },
        { "Exif.Photo.Gamma", "伽马值" },
        { "Exif.Photo.MakerNote", "制造商备注" },
        { "Exif.Iop.InteroperabilityIndex", "互操作性索引" },
        { "Exif.Iop.InteroperabilityVersion", "互操作性版本" },
        { "Exif.Iop.RelatedImageFileFormat", "相关图像文件格式" },
        { "Exif.Iop.RelatedImageWidth", "相关图像宽度" },
        { "Exif.Iop.RelatedImageLength", "相关图像长度" },
        { "Exif.GPSInfo.GPSVersionID", "GPS版本ID" },
        { "Exif.GPSInfo.GPSLatitudeRef", "GPS纬度参考" },
        { "Exif.GPSInfo.GPSLatitude", "GPS纬度" },
        { "Exif.GPSInfo.GPSLongitudeRef", "GPS经度参考" },
        { "Exif.GPSInfo.GPSLongitude", "GPS经度" },
        { "Exif.GPSInfo.GPSAltitudeRef", "GPS高度参考" },
        { "Exif.GPSInfo.GPSAltitude", "GPS高度" },
        { "Exif.GPSInfo.GPSTimeStamp", "GPS时间戳" },
        { "Exif.GPSInfo.GPSSatellites", "GPS卫星数" },
        { "Exif.GPSInfo.GPSStatus", "GPS状态" },
        { "Exif.GPSInfo.GPSMeasureMode", "GPS测量模式" },
        { "Exif.GPSInfo.GPSDOP", "GPS精度因子" },
        { "Exif.GPSInfo.GPSSpeedRef", "GPS速度参考" },
        { "Exif.GPSInfo.GPSSpeed", "GPS速度" },
        { "Exif.GPSInfo.GPSTrackRef", "GPS方向参考" },
        { "Exif.GPSInfo.GPSTrack", "GPS方向" },
        { "Exif.GPSInfo.GPSImgDirectionRef", "GPS图像方向参考" },
        { "Exif.GPSInfo.GPSImgDirection", "GPS图像方向" },
        { "Exif.GPSInfo.GPSMapDatum", "GPS地图基准" },
        { "Exif.GPSInfo.GPSDestLatitudeRef", "GPS目的地纬度参考" },
        { "Exif.GPSInfo.GPSDestLatitude", "GPS目的地纬度" },
        { "Exif.GPSInfo.GPSDestLongitudeRef", "GPS目的地经度参考" },
        { "Exif.GPSInfo.GPSDestLongitude", "GPS目的地经度" },
        { "Exif.GPSInfo.GPSDestBearingRef", "GPS目的地方位参考" },
        { "Exif.GPSInfo.GPSDestBearing", "GPS目的地方位" },
        { "Exif.GPSInfo.GPSDestDistanceRef", "GPS目的地距离参考" },
        { "Exif.GPSInfo.GPSDestDistance", "GPS目的地距离" },
        { "Exif.GPSInfo.GPSProcessingMethod", "GPS处理方法" },
        { "Exif.GPSInfo.GPSAreaInformation", "GPS区域信息" },
        { "Exif.GPSInfo.GPSDateStamp", "GPS日期戳" },
        { "Exif.GPSInfo.GPSDifferential", "GPS差分校正" },
        { "Exif.GPSInfo.GPSHPositioningError", "GPS水平定位误差" },
        { "Exif.MpfInfo.MPFVersion", "MPF版本" },
        { "Exif.MpfInfo.MPFNumberOfImages", "MPF图像数量" },
        { "Exif.MpfInfo.MPFImageList", "MPF图像列表" },
        { "Exif.MpfInfo.MPFImageUIDList", "MPF图像UID列表" },
        { "Exif.MpfInfo.MPFTotalFrames", "MPF总帧数" },
        { "Exif.MpfInfo.MPFIndividualNum", "MPF个体编号" },
        { "Exif.MpfInfo.MPFPanOrientation", "MPF全景方向" },
        { "Exif.MpfInfo.MPFPanOverlapH", "MPF水平重叠" },
        { "Exif.MpfInfo.MPFPanOverlapV", "MPF垂直重叠" },
        { "Exif.MpfInfo.MPFBaseViewpointNum", "MPF基准视点编号" },
        { "Exif.MpfInfo.MPFConvergenceAngle", "MPF会聚角" },
        { "Exif.MpfInfo.MPFBaselineLength", "MPF基线长度" },
        { "Exif.MpfInfo.MPFVerticalDivergence", "MPF垂直偏差" },
        { "Exif.MpfInfo.MPFAxisDistanceX", "MPF X轴距离" },
        { "Exif.MpfInfo.MPFAxisDistanceY", "MPF Y轴距离" },
        { "Exif.MpfInfo.MPFAxisDistanceZ", "MPF Z轴距离" },
        { "Exif.MpfInfo.MPFYawAngle", "MPF偏航角" },
        { "Exif.MpfInfo.MPFPitchAngle", "MPF俯仰角" },
        { "Exif.MpfInfo.MPFRollAngle", "MPF翻滚角" },
    };

};
