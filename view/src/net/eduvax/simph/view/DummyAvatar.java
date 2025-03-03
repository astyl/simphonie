/*
 * @file DummyAvatar.java
 *
 * Copyright 2022 Sebastien Devaux. All rights reserved.
 * Use is subject to license terms.
 *
 * $Id$
 * $Date$
 */
package net.eduvax.simph.view;

import com.jme3.asset.AssetManager;
import com.jme3.effect.ParticleEmitter;
import com.jme3.effect.ParticleMesh.Type;
import com.jme3.material.Material;
import com.jme3.math.ColorRGBA;
import com.jme3.math.Quaternion;
import com.jme3.math.Transform;
import com.jme3.math.Vector3f;
import com.jme3.renderer.ViewPort; 
import com.jme3.renderer.queue.RenderQueue;
import com.jme3.scene.Geometry;
import com.jme3.scene.Node;
import com.jme3.scene.Spatial;
import com.jme3.scene.shape.Box;
import com.jme3.scene.shape.Cylinder;
import com.jme3.scene.shape.Sphere;

/**
 *
 */
public class DummyAvatar extends Avatar implements ISceneComposition {
    @Override public void build(View view) {
        AssetManager assetManager=view.getAssetManager();

        Geometry head=new Geometry("head",new Sphere(20,20,0.5f));
        head.setLocalTranslation(0,1,0);
        _tail=new Geometry("tail",new Cylinder(20,20,0.5f,2,true));
        float f[]={(float)Math.PI/2,0,0};
        Quaternion q=new Quaternion(f);
        _tail.setLocalRotation(q);
        _exhaust=new ParticleEmitter("exhaust",Type.Triangle,100);
        _exhaust.setLocalTranslation(0,-1,0);
        _exhaust.getParticleInfluencer().setVelocityVariation(1);
        _node = new Node("dummy");
        _node.attachChild(head);
        _node.attachChild(_tail);
        _node.attachChild(_exhaust);
        Material mat = new Material(assetManager, "Common/MatDefs/Light/Lighting.j3md");
        mat.setBoolean("UseMaterialColors",true);
        mat.setColor("Ambient",new ColorRGBA(1,1,1,0.5f));
        mat.setColor("Diffuse",new ColorRGBA(1,1,1,0.5f));
        mat.setColor("Specular",ColorRGBA.Yellow);
        mat.setFloat("Shininess", 96f);
        _node.setMaterial(mat);
        mat=new Material(assetManager,"Common/MatDefs/Misc/Particle.j3md");
        _exhaust.setImagesX(15);
        mat.setTexture("Texture", assetManager.loadTexture("res/textures/smoke.png"));
        _exhaust.setMaterial(mat);
        view.getRootNode().attachChild(_node);
    }
    @Override public void update(float tpf) {
        _node.setLocalTranslation(getLocation());
        _node.setLocalRotation(getAttitude());

        Avatar.AttrChange ac=pollAttrChange();
        while (ac!=null) {
            if ("smoke".equals(ac._name)) {
                _exhaust.setParticlesPerSec((float)ac._value*10f);
            }
            else if ("split".equals(ac._name)) {
                _split=true;
            }
            ac=pollAttrChange();
        }
        if (_split) {
            Vector3f l=_tail.getLocalTranslation();
            l.setY(l.getY()-0.1f);
        }
    }
    private Node _node;
    private ParticleEmitter _exhaust;
    private Geometry _tail;
    private boolean _split=false;
}
