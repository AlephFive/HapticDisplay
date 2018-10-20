using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SceneController2 : MonoBehaviour {
	
	public Camera m_camera;

	private bool fmove = false;
	private float speed = 0;
	

	void Update () 
	{
		//右滑进入scene3
		if (m_camera.transform.position.x > 81 && Input.GetMouseButton(0))
			fmove = true;
		
		//移动摄像机到下一幕
		if (fmove && m_camera.transform.position.x <= 126) 
		{
			m_camera.transform.Translate (Vector3.right * speed * Time.deltaTime);
			if (m_camera.transform.position.x < 104)
			{
				speed++;
			} 
			else
			{
				if (speed != 0)
					speed--;
			}
			if (m_camera.transform.position.x > 126)
				fmove = false;
		}
		
	}
}
