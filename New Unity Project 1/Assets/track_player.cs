using UnityEngine;
using System.Collections;

public class track_player : MonoBehaviour {
	Transform player;
	float offsetz;
	float offsety;
	float offsetx;
	// Use this for initialization
	void Start () {
		GameObject player_go = GameObject.FindGameObjectWithTag ("Player");
		if (player_go == null) 
		{
			Debug.LogError ("no player");
			return;
		}
		player = player_go.transform;
		offsetz = transform.position.z - player.position.z;
		offsety = transform.position.y - player.position.y;
		offsetx = transform.position.x - player.position.x;
	}
	
	// Update is called once per frame
	void Update () {
		if (player != null)
		{
			Vector3 pos = transform.position;
			pos.y = player.position.y + offsety;
			pos.z = player.position.z + offsetz;
			pos.x = player.position.x + offsetx;
			transform.position = pos;
		}
	}
}
