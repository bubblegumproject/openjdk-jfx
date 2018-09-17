/*
 * Copyright (c) 2018, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

#pragma once

#include "BitmapTexture.h"
#include "ImageBuffer.h"
#include "IntRect.h"
#include "IntSize.h"

namespace WebCore {

class GraphicsContext;

class BitmapTextureJava : public BitmapTexture {
public:
    static Ref<BitmapTexture> create() { return adoptRef(*new BitmapTextureJava); }
    IntSize size() const override { return m_image->internalSize(); }
    void didReset() override;
    bool isValid() const override { return m_image.get(); }
    inline GraphicsContext* graphicsContext() { return m_image ? &(m_image->context()) : nullptr; }
    void updateContents(Image*, const IntRect&, const IntPoint&, UpdateContentsFlag) override;
    void updateContents(TextureMapper&, GraphicsLayer*, const IntRect& target, const IntPoint& offset, UpdateContentsFlag, float scale = 1) override;
    void updateContents(const void*, const IntRect& target, const IntPoint& sourceOffset, int bytesPerLine, UpdateContentsFlag) override;
    RefPtr<BitmapTexture> applyFilters(TextureMapper&, const FilterOperations&) override;
    ImageBuffer* image() const { return m_image.get(); }

private:
    BitmapTextureJava() { }
    std::unique_ptr<ImageBuffer> m_image;
};

}
