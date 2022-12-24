/* Copyright 2012-2020 Matthew Reid
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "VolumeCloudsComposite.h"
#include "SkyboltVis/OsgStateSetHelpers.h"
#include "SkyboltVis/OsgTextureHelpers.h"

namespace skybolt {
namespace vis {

static osg::StateSet* createTexturedQuadStateSet(osg::ref_ptr<osg::Program> program)
{
	osg::StateSet* stateSet = new osg::StateSet();
	stateSet->setAttributeAndModes(program, osg::StateAttribute::ON);
	stateSet->addUniform(createUniformSampler2d("colorTexture", 0));
	stateSet->addUniform(createUniformSampler2d("depthTexture", 1));
	stateSet->setMode(GL_CULL_FACE, osg::StateAttribute::OFF);
	return stateSet;
}

VolumeCloudsComposite::VolumeCloudsComposite(const VolumeCloudsCompositeConfig& config) :
	ScreenQuad(createTexturedQuadStateSet(config.compositorProgram))
{
	makeStateSetTransparent(*mTransform->getOrCreateStateSet(), vis::TransparencyMode::PremultipliedAlpha, RenderBinId::Clouds);
	setColorTexture(config.colorTexture);
	setDepthTexture(config.depthTexture);
}

void VolumeCloudsComposite::setColorTexture(osg::ref_ptr<osg::Texture> texture)
{
	mTransform->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);
}

void VolumeCloudsComposite::setDepthTexture(osg::ref_ptr<osg::Texture> texture)
{
	mTransform->getOrCreateStateSet()->setTextureAttributeAndModes(1, texture, osg::StateAttribute::ON);
}

} // namespace vis
} // namespace skybolt
